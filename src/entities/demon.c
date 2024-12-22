#include "../../include/entities/demon.h"
#include <stdlib.h>
#include <time.h>

Demon createDemon(){

    Demon demon;// = (Demon*)malloc(sizeof(Demon));
    demon.alive = true;
    demon.status = NORMAL;

    demon.health = 100;
    demon.evil = 50;

    demon.position = (Vec2){
        .x = (float)(rand() % 151),
        .y = (float)(rand() % 151)
    };
    demon.velocity = (Vec2){0.0f, 0.0f};
    demon.acceleration = (Vec2){0.0f, 0.0f};

    demon.sprite = (SDL_Rect){0, 0, 16, 16};

    demon.collider = (SDL_Rect){0, 0, 8, 8};

    demon.attack = false;

    demon.counter = 0;
    demon.run = 0;

    return demon;
}
