#include "audio.h"

void Audio_Init(AudioManager *audio)
{
    audio->jump = LoadSound("assets/8bit_jump_soundEffect.mp3");
    audio->bgMusic = LoadMusicStream("assets/8bit_regular_backgroundMusic.mp3");

    PlayMusicStream(audio->bgMusic);
}

void Audio_Update(AudioManager *audio)
{
    UpdateMusicStream(audio->bgMusic);
}

void Audio_Unload(AudioManager *audio)
{
    UnloadSound(audio->jump);
    UnloadMusicStream(audio->bgMusic);
}
