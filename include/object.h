#pragma once

typedef enum ObjectTag
{
    TAG_NONE,
    TAG_GROUND,
    TAG_COLLECTABLE,
    TAG_ENEMY
} ObjectTag;

typedef struct GameObject
{
    Vector2 position;
    Vector2 size;
    ObjectTag tag;
    bool active;
} GameObject;
