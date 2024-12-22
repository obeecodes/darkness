#pragma once

#include "../structures/vec2.h"
#include <SDL.h>
#include <stdbool.h>

typedef enum {
    IDLE,
    RUNNING,
    JUMPING,
    PRAYING,
    ATTACKING
} PlayerState;

typedef struct Player{
    int maxHealth;
    int health;
    int faith;

    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    SDL_Rect sprite;

    PlayerState state;

    int counter;

    SDL_Rect collider;

    bool right;
    bool fireToIce;


} Player;


Player* createPlayer();