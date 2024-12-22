#include "../../include/entities/player.h"
#include <stdlib.h>

Player* createPlayer() {
    Player* player = (Player*)malloc(sizeof(Player));

    player->maxHealth = 10000;
    player->health = 10000;
    player->faith = 50;
    player->sound = Mix_LoadWAV("assets/sounds/hit.wav");

    player->position = (Vec2){16 * 5, 0.0f};
    player->velocity = (Vec2){0.0f, 0.0f};
    player->acceleration = (Vec2){0.0f, 0.0f};

    player->sprite = (SDL_Rect){0, 0, 16, 16};

    player->collider = (SDL_Rect){0, 0, 8, 8};

    player->state = IDLE;

    player->counter = 0;

    player->fireToIce = 0;

    return player;
}

