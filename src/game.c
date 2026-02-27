#include "game.h"
#include "object.h"
#include "stdio.h"
#include <string.h>
#include <stdio.h>


ObjectTag Tag_FromString(const char* str)
{
    if (strcmp(str, "GROUND") == 0) return TAG_GROUND;
    if (strcmp(str, "COLLECTABLE") == 0) return TAG_COLLECTABLE;
    if (strcmp(str, "ENEMY") == 0) return TAG_ENEMY;
    return TAG_NONE;
}

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

void Game_LoadLevel(Game *game, const char* filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
	printf("Failed to open levle file: %s\n", filename);
	return;
    }

    game->objectCount = 0;

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
	if (line[0] == '#' || line[0] == '\n')
	{
	    continue;
	}

	float x, y, width, height;
	char tagString[32];
	int result = sscanf(line, "%f,%f,%f,%f,%31[^\n]", &x, &y, &width, &height, tagString);

	if (result == 5)
	{
	    Add_Object(game, (Vector2){x, y}, (Vector2){width, height}, Tag_FromString(tagString));
	}
	else
	{
	    printf("Failed to parse line: %s\n", line);
	}
    }
    fclose(file);
}

void Game_Init(Game *game, int width, int height)
{
    game->screenWidth = width;
    game->screenHeight = height;

    game->objectCount = 0;
    Player_Init(&game->player, (width)/2, (height)/2);
    Audio_Init(&game->audio);

    Game_LoadLevel(game, "assets/levels/level1.csv");
}

void Game_Update(Game *game)
{
    float deltaTime = GetFrameTime();
    bool jumped = Player_Update(&game->player, deltaTime,game->objects, game->objectCount);
    
    if (jumped)
    {
	PlaySound(game->audio.jump);
    }

    if (game->player.isCollected)
    {
	PlaySound(game->audio.collect);
	game->player.isCollected = false;
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

	    case TAG_COLLECTABLE:
		DrawCircle(obj->position.x, obj->position.y, obj->size.x, ORANGE);
		break;
	    default:
                break;
        }
    }

    char scoreText[50];
    sprintf(scoreText, "%d / 3", game->player.score);
    DrawText(scoreText, game->screenWidth/2, 0, 30, BLACK);
    DrawCircle(0, 0, 90, YELLOW);
    Player_Draw(&game->player);
}

void Game_Close(Game *game)
{
    Audio_Unload(&game->audio);
}
