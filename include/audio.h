#pragma once

#include "raylib.h"

typedef struct AudioManager
{
    Sound jump;
    Music bgMusic;
} AudioManager;

void Audio_Init(AudioManager *audio);
void Audio_Update(AudioManager *audio);
void Audio_Unload(AudioManager *audio);
