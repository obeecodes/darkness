#include "../../include/entities/hail.h"

Hail createHail(Vec2 playerPos, bool dir){
    Hail hail;
    hail.position.x = playerPos.x;
    hail.position.y = playerPos.y - 6;
    hail.sound = Mix_LoadWAV("assets/sounds/ice.wav");
    Mix_PlayChannel(-1, hail.sound, 0);
    Vec2 front = playerPos;

    int dx;
    if(dir){
        dx = 16 * 3;
        hail.flip = true;
    }else{
        dx = -16 * 3;
        hail.flip = false;
    }
    front.x += dx;
    front.y += 16;

    hail.velocity = vec2_to_from(&front, &hail.position);
    vec2_normalize(&hail.velocity);
    //hail.velocity.x = 1;
    //hail.velocity.y = 1;

    vec2_multiply(&hail.velocity, 4);


    SDL_Rect collider;
    collider.x = hail.position.x + 6;
    collider.y = hail.position.y + 6;
    collider.w = 4;
    collider.h = 4;


    hail.collider = collider;

    hail.sprite.x = 16 * 4;
    hail.sprite.y = 16 * 4;
    hail.sprite.w = 16;
    hail.sprite.h = 16;

    return hail;
}