#pragma once

#include "../structures/vec2.h"
#include <SDL.h>
#include <stdbool.h>
#include <SDL_mixer.h>

typedef struct Hail{
    Vec2 velocity;
    Vec2 position;

    SDL_Rect sprite;
    SDL_Rect collider;
    Mix_Chunk* sound;

    bool flip;

} Hail;

Hail createHail(Vec2 playerPos, bool dir);