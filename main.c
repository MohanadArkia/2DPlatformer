#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main ()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My First Raylib project");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
	BeginDrawing();
	ClearBackground(BLUE);

	DrawRectangle(0, (SCREEN_HEIGHT)-40, SCREEN_WIDTH, 40, GREEN);
	DrawCircle(0, 0, 90, YELLOW);
	

	EndDrawing();
    }
    CloseWindow();
    return 0;
}
