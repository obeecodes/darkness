#pragma once

#include "../structures/vec2.h"
#include <stdbool.h>

#include <SDL.h>

typedef enum {
    NORMAL,
    FROST,
    BURN,
} STATUS;

typedef struct Demon {
    int health;
    int evil;

    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    SDL_Rect sprite;

    SDL_Rect collider;
    bool alive;

    STATUS status;

    bool attack;
    int counter;
    int run;
} Demon;

Demon createDemon();