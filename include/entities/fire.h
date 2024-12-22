#pragma once

#include "../structures/vec2.h"
#include <SDL.h>
#include <stdbool.h>
#include <SDL_mixer.h>

typedef struct Fire{
    Vec2 velocity;
    Vec2 position;

    SDL_Rect sprite;
    SDL_Rect collider;

    Mix_Chunk* sound;

    int frame;
    int count;

    bool flip;
} Fire;

Fire createFire(Vec2 playerPos, bool dir);