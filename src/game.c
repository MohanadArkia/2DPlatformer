#include "game.h"

void Game_Init(Game *game, int width, int height)
{
    game->screenWidth = width;
    game->screenHeight = height;

    Player_Init(&game->player, (width)/2, (height)/2);
    Audio_Init(&game->audio);

    // Create ground floor
    game->objects[0].position = (Vector2){0, height - 40};
    game->objects[0].size = (Vector2){width, 40};
    game->objects[0].tag = TAG_GROUND;
    game->objects[0].active = true;

    // Create a platform
    game->objects[1].position = (Vector2){80, height - 90};
    game->objects[1].size = (Vector2){100, 40};
    game->objects[1].tag = TAG_GROUND;
    game->objects[1].active = true;

    game->objectCount = 2;
}

void Game_Update(Game *game)
{
    float deltaTime = GetFrameTime();
    bool jumped = Player_Update(&game->player, deltaTime,game->objects, game->objectCount);
    
    if (jumped)
    {
	PlaySound(game->audio.jump);
    }
    Audio_Update(&game->audio);
}

void Game_Draw(Game *game)
{
    ClearBackground(BLUE);

    for (int i = 0; i < game->objectCount; i++)
    {
        GameObject *obj = &game->objects[i];
        if (!obj->active)
	{
	    continue;
	}

        switch (obj->tag)
        {
            case TAG_GROUND:
                DrawRectangle(obj->position.x, obj->position.y, obj->size.x, obj->size.y, GREEN);
                break;

	    default:
                break;
        }
    }


    DrawCircle(0, 0, 90, YELLOW);
    Player_Draw(&game->player);
}

void Game_Close(Game *game)
{
    Audio_Unload(&game->audio);
}
