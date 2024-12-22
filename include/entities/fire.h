#pragma once

#include "../structures/vec2.h"
#include <SDL.h>
#include <stdbool.h>

typedef struct Fire{
    Vec2 velocity;
    Vec2 position;

    SDL_Rect sprite;
    SDL_Rect collider;

    int frame;
    int count;

    bool flip;
} Fire;

Fire createFire(Vec2 playerPos, bool dir);