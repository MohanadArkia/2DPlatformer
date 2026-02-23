#include "player.h"

void Player_Init(Player *player, float x, float y)
{
    player->position = (Vector2){x, y};
    player->speed = 5.0f;
    player->radius = 30.0f;
}

void Player_Update(Player *player)
{
    if (IsKeyDown(KEY_RIGHT))
    {
	player->position.x += player->speed;
    }

    if (IsKeyDown(KEY_LEFT))
    {
	player->position.x -= player->speed;
    }

    if (IsKeyDown(KEY_UP))
    {
	player->position.y -= player->speed;
    }

    if (IsKeyDown(KEY_DOWN))
    {
	player->position.y += player->speed;
    }
}

void Player_Draw(Player *player)
{
    DrawCircleV(player->position, player->radius, PINK);
}
