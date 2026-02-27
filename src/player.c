#include "player.h"
#include "game.h"

void Player_Init(Player *player, float x, float y)
{
    player->position = (Vector2){ x, y };
    player->velocity = (Vector2){ 0, 0 };
    player->radius = 30.0f;
    player->moveSpeed = 300.0f;
    player->jumpForce = 200.0f;
    player->isGrounded = false;
    player->score = 0;
    player->isCollected = false;
}

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

	if (obj->tag == TAG_GROUND)
	{
            float playerBottom = player->position.y + player->radius;
            float playerLeft = player->position.x - player->radius;
            float playerRight = player->position.x + player->radius;
            float objTop = obj->position.y;
            float objLeft = obj->position.x;
            float objRight = obj->position.x + obj->size.x;

            bool collidingX = playerRight > objLeft && playerLeft < objRight;
            bool collidingY = playerBottom > objTop && player->position.y < objTop + obj->size.y;

            if (collidingX && collidingY && player->velocity.y >= 0)
            {
                // Snap player to top of object
                player->position.y = objTop - player->radius;
                player->velocity.y = 0;
                player->isGrounded = true;
            }
	}
	if (obj->tag == TAG_COLLECTABLE)
	{
	    float playerLeft = player->position.x - player->radius;
	    float playerRight = player->position.x + player->radius;
	    float playerTop = player->position.y - player->radius;
	    float playerBottom = player->position.y + player->radius;

	    float objLeft = obj->position.x;
	    float objRight = obj->position.x + obj->size.x;
	    float objTop = obj->position.y;
	    float objBottom = obj->position.y + obj->size.y;

	    bool collidingX = playerRight > objLeft && playerLeft < objRight;
	    bool collidingY = playerBottom > objTop && playerTop < objBottom;

	    if (collidingX && collidingY)
	    {
		obj->active = false;
		player->score += 1;
		player->isCollected = true;
	    }
	}
    }
    return jumped;
}

void Player_Draw(Player *player)
{
    DrawCircleV(player->position, player->radius, PINK);
}
