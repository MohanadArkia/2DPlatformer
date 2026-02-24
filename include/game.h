#pragma once

#include "raylib.h"
#include "player.h"
#include "audio.h"
#include "object.h"

#define MAX_OBJECTS 128

typedef struct Game
{
    Player player;
    int screenWidth;
    int screenHeight;
    AudioManager audio;

    GameObject objects[MAX_OBJECTS];
    int objectCount;
} Game;

void Game_Init(Game *game, int width, int height);
void Game_Update(Game *game);
void Game_Draw(Game *game);
void Game_Close(Game *game);
