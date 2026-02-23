#include "raylib.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450

int main ()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My First Raylib project");
    SetTargetFPS(60);

    Vector2 playerPosition = {(float)SCREEN_WIDTH/2, (float)SCREEN_HEIGHT/2};
    float playerSpeed = 5.0f;

    while (!WindowShouldClose())
    {

	if (IsKeyDown(KEY_RIGHT))
	{
	    playerPosition.x += playerSpeed;
	}

	if (IsKeyDown(KEY_LEFT))
	{
	    playerPosition.x -= playerSpeed;
	}

	if (IsKeyDown(KEY_UP))
	{
	    playerPosition.y -= playerSpeed;
	}

	if (IsKeyDown(KEY_DOWN))
	{
	    playerPosition.y += playerSpeed;
	}

	BeginDrawing();
	ClearBackground(BLUE);

	DrawRectangle(0, (SCREEN_HEIGHT)-40, SCREEN_WIDTH, 40, GREEN);
	DrawCircle(0, 0, 90, YELLOW);

	DrawCircleV(playerPosition, 30, PINK);

	EndDrawing();
    }
    CloseWindow();
    return 0;
}
