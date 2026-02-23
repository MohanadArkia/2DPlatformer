#pragma once

#include "raylib.h"
#include "player.h"

typedef struct Game
{
    Player player;
    int screenWidth;
    int screenHeight;
} Game;


void Game_Init(Game *game, int width, int height);
void Game_Update(Game *game);
void Game_Draw(Game *game);
void Game_Close(Game *game);
