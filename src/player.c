#include "player.h"
#include "game.h"

void Player_Init(Player *player, float x, float y)
{
    player->position = (Vector2){ x, y };
    player->velocity = (Vector2){ 0, 0 };
    player->radius = 30.0f;
    player->moveSpeed = 300.0f;
    player->jumpForce = 500.0f;
    player->isGrounded = false;
}

bool Player_Update(Player *player, float deltaTime, int screenHeight)
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

    // Ground collision
    float groundY = screenHeight - 40;
    if (player->position.y + player->radius >= groundY)
    {
        player->position.y = groundY - player->radius;
        player->velocity.y = 0;
        player->isGrounded = true;
    }
    return jumped;
}

void Player_Draw(Player *player)
{
    DrawCircleV(player->position, player->radius, PINK);
}
