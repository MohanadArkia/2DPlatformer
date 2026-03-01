#include "player.h"
#include "game.h"

// TODO: Refactor
bool CheckCollisionPlayerObject(Player* player, GameObject* obj)
{
    float playerLeft   = player->position.x - player->radius;
    float playerRight  = player->position.x + player->radius;
    float playerTop    = player->position.y - player->radius;
    float playerBottom = player->position.y + player->radius;

    float objLeft   = obj->position.x;
    float objRight  = obj->position.x + obj->size.x;
    float objTop    = obj->position.y;
    float objBottom = obj->position.y + obj->size.y;

    bool overlapX = playerRight > objLeft && playerLeft < objRight;
    bool overlapY = playerBottom > objTop && playerTop < objBottom;

    return overlapX && overlapY;
}

void HandleGroundCollision(Player* player, GameObject* obj)
{
    if (!CheckCollisionPlayerObject(player, obj))
    {
	return;
    }
    if (player->velocity.y >= 0)
    {
	player->position.y = obj->position.y - player->radius;
	player->velocity.y = 0;
	player->isGrounded = true;
    }
}

void HandleCollectableCollision(Player* player, GameObject* obj)
{
    if (!CheckCollisionPlayerObject(player, obj))
    {
	return;
    }

    obj->active = false;
    player->score += 1;
    player->isCollected = true;
}

// TODO: Refactor
void HandlePlatformCollision(Player *player, GameObject *obj)
{
    if (!CheckCollisionPlayerObject(player, obj))
    {
	return;
    }

    float playerLeft   = player->position.x - player->radius;
    float playerRight  = player->position.x + player->radius;
    float playerTop    = player->position.y - player->radius;
    float playerBottom = player->position.y + player->radius;

    float objLeft   = obj->position.x;
    float objRight  = obj->position.x + obj->size.x;
    float objTop    = obj->position.y;
    float objBottom = obj->position.y + obj->size.y;

    float overlapLeft   = playerRight - objLeft;
    float overlapRight  = objRight - playerLeft;
    float overlapTop    = playerBottom - objTop;
    float overlapBottom = objBottom - playerTop;

    float minX = (overlapLeft < overlapRight) ? overlapLeft : overlapRight;
    float minY = (overlapTop < overlapBottom) ? overlapTop : overlapBottom;

    if (minX < minY)
    {
        if (overlapLeft < overlapRight)
	{
            player->position.x -= overlapLeft;
	}
        else
	{
            player->position.x += overlapRight;
	}
        player->velocity.x = 0;
    }
    else
    {
        if (overlapTop < overlapBottom)
        {
            player->position.y -= overlapTop;
            player->isGrounded = true;
        }
        else
        {
            player->position.y += overlapBottom;
        }

        player->velocity.y = 0;
    }
}

void HandleEnemyCollision(Player *player, GameObject *obj)
{
    if (!CheckCollisionPlayerObject(player, obj))
    {
	return;
    }

    player->position.x = 0;
    player->position.y = 350;
    player->velocity = (Vector2){0, 0};
}

void Player_Init(Player *player, float x, float y)
{
    player->position = (Vector2){x, y};
    player->velocity = (Vector2){0, 0};
    player->radius = 25.0f;
    player->moveSpeed = 300.0f;
    player->jumpForce = 330.0f;
    player->isGrounded = false;
    player->score = 0;
    player->isCollected = false;
}

// TODO: Refactor
bool Player_Update(Player *player, float deltaTime, GameObject *objects, int objectCount)
{
    const float gravity = 900.0f;
    bool jumped = false;
    player->velocity.y += gravity * deltaTime;

    if (IsKeyDown(KEY_A))
    {
        player->velocity.x = -player->moveSpeed;
    }
    else if (IsKeyDown(KEY_D))
    {
        player->velocity.x = player->moveSpeed;
    }
    else
    {
        player->velocity.x = 0;
    }

    if (IsKeyPressed(KEY_SPACE) && player->isGrounded)
    {
        player->velocity.y = -player->jumpForce;
        player->isGrounded = false;
        jumped = true;
    }

    if (player->position.x > 770)
    {
        player->position.x = 770;
    }

    if (player->position.x < 30)
    {
        player->position.x = 30;
    }

    player->position.x += player->velocity.x * deltaTime;
    player->position.y += player->velocity.y * deltaTime;

    // Tag based collision
    player->isGrounded = false;
    for (int i = 0; i < objectCount; i++)
    {
	GameObject *obj = &objects[i];
	if (!obj->active)
	{
	    continue;
	}

	switch(obj->tag)
	{
	    case TAG_GROUND:
		HandleGroundCollision(player, obj);
		break;
	    case TAG_COLLECTABLE:
		HandleCollectableCollision(player, obj);
		break;
	    case TAG_PLATFORM:
		HandlePlatformCollision(player, obj);
		break;
	    case TAG_ENEMY:
		HandleEnemyCollision(player, obj);
		break;
	    }
	}
	if (player->score == 3)
	{
	    DrawText("YOU WON!!", 130, 200, 100, RED);
	}
	return jumped;
    }

void Player_Draw(Player *player)
{
    DrawCircleV(player->position, player->radius, PINK);
}
