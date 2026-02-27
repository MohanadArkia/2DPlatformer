#pragma once

#include "raylib.h"
#include "object.h"

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

    int score;
} Player;

void Player_Init(Player *player, float x, float y);
bool Player_Update(Player *player, float deltaTime, GameObject *objects, int objectCount);
void Player_Draw(Player *player);
