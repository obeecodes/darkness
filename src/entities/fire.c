#include "../../include/entities/fire.h"

Fire createFire(Vec2 playerPos, bool dir){
    Fire fire;
    fire.position.x = playerPos.x;
    fire.position.y = playerPos.y - 6;

    Vec2 front = playerPos;

    int dx;
    if(dir){
        dx = 16 * 3;
        fire.flip = true;
    }else{
        dx = -16 * 3;
        fire.flip = false;
    }
    front.x += dx;
    front.y += 16;

    fire.velocity = vec2_to_from(&front, &fire.position);
    vec2_normalize(&fire.velocity);
    //fire.velocity.x = 1;
    //fire.velocity.y = 1;

    vec2_multiply(&fire.velocity, 3);


    SDL_Rect collider;
    collider.x = fire.position.x + 6;
    collider.y = fire.position.y + 6;
    collider.w = 4;
    collider.h = 4;


    fire.collider = collider;

    fire.frame = 0;
    fire.count = 0;

    fire.sprite.x = 16 * 0;
    fire.sprite.y = 16 * 4;
    fire.sprite.w = 16;
    fire.sprite.h = 16;

    return fire;
}