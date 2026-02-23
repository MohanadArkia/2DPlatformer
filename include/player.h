#pragma once

#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    float speed;
    float radius;
} Player;

void Player_Init(Player *player, float x, float y);
void Player_Update(Player *player);
void Player_Draw(Player *player);
