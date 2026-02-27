#include "game.h"
#include "object.h"

void Add_Object(Game *game, Vector2 position, Vector2 size, ObjectTag tag)
{
    if (game->objectCount >= MAX_OBJECTS)
    {
	return;
    }

    GameObject *obj = &game->objects[game->objectCount++];

    obj->position = position;
    obj->size = size;
    obj->tag = tag;
    obj->active = true;
}

void Game_Init(Game *game, int width, int height)
{
    game->screenWidth = width;
    game->screenHeight = height;

    game->objectCount = 0;
    Player_Init(&game->player, (width)/2, (height)/2);
    Audio_Init(&game->audio);

    Add_Object(game, (Vector2){0, height - 40}, (Vector2){width, 40}, TAG_GROUND);
    Add_Object(game, (Vector2){80, height - 100}, (Vector2){150, 30}, TAG_GROUND);
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

    DrawText("Score: ", (game->screenWidth)/2, 0, 30, BLACK);
    DrawCircle(0, 0, 90, YELLOW);
    Player_Draw(&game->player);
}

void Game_Close(Game *game)
{
    Audio_Unload(&game->audio);
}
