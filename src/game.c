#include "game.h"

void Game_Init(Game *game, int width, int height)
{
    game->screenWidth = width;
    game->screenHeight = height;

    Player_Init(&game->player, (width)/2, (height)/2);
    Audio_Init(&game->audio);
}

void Game_Update(Game *game)
{
    float deltaTime = GetFrameTime();
    bool jumped = Player_Update(&game->player, deltaTime, game->screenHeight);
    
    if (jumped)
    {
	PlaySound(game->audio.jump);
    }
    Audio_Update(&game->audio);
}

void Game_Draw(Game *game)
{
    ClearBackground(BLUE);

    DrawRectangle(0, game->screenHeight - 40, game->screenWidth, 40, GREEN);

    DrawRectangle(80, game->screenHeight-90, 100, 40, GREEN);

    DrawCircle(0, 0, 90, YELLOW);

    Player_Draw(&game->player);
}

void Game_Close(Game *game)
{
    Audio_Unload(&game->audio);
}
