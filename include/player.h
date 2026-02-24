#pragma once

#include "raylib.h"

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    
    float radius;
    float mass;
    float moveSpeed;
    float jumpForce;

    bool isGrounded;
} Player;

void Player_Init(Player *player, float x, float y);
void Player_Update(Player *player, float deltaTime, int screenHeight);
void Player_Draw(Player *player);
