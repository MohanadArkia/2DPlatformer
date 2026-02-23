#include "raylib.h"
#include "game.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main ()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Simple 2D Platformer");
    SetTargetFPS(60);

    Game game;
    Game_Init(&game, SCREEN_WIDTH, SCREEN_HEIGHT);
 
    while (!WindowShouldClose())
    {
	Game_Update(&game);
	BeginDrawing();

	Game_Draw(&game);
	
	EndDrawing();
    }
    //Game_Close(&game);
    CloseWindow();
    return 0;
}
