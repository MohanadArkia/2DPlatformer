#include "game.h"

void Game_Init(Game *game, int width, int height)
{
    game->screenWidth = width;
    game->screenHeight = height;

    Player_Init(&game->player, (width)/2, (height)/2);
}

void Game_Update(Game *game)
{
    Player_Update(&game->player);
}

void Game_Draw(Game *game)
{
    ClearBackground(BLUE);

    DrawRectangle(0, game->screenHeight - 40, game->screenWidth, 40, GREEN);
    DrawCircle(0, 0, 90, YELLOW);

    Player_Draw(&game->player);
}

//void Game_Close(Game *game)
//{
//}
