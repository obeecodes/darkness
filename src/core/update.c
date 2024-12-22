#include "../../include/core/update.h"
#include "../../include/structures/vec2.h"
#include "../../include/structures/stack.h"
#include "../../include/core/sprite.h"
#include "../../include/core/renderer.h"
#include "../../include/core/globals.h"

#include <SDL.h>
#include <stdio.h>

void menuStateUpdate(GameState* state){
    SDL_Rect viewport;
    SDL_RenderGetViewport(renderer, &viewport);
    SDL_Rect button;
    button.x = viewport.w/2 - 4;
    button.y = viewport.h/2 + 4;
    button.w = 24;
    button.h = 12;
    state->button = button;

    SDL_Rect mouse = {state->mousePosX, state->mousePosY, 1, 1};

    if(state->mouseClick && SDL_HasIntersection(&button, &mouse)){
        push(&gameStates, createPlayState());
    }
}

void playStateUpdate(GameState* state){
    updatePositions(state);
    updateSprite(state);
    updateCamera(state);
    handleCollisions(state);
}

void pauseStateUpdate(GameState* state){
    if(state->stack->top == 2){
        updateSprite(gameStates.data[gameStates.top - 1]);
    }
}

void gameOverStateUpdate(GameState* state){
}

void updatePositions(GameState* state){
    Player* player = state->player;

    //vec2_multiply(&player->velocity, 0.5);
    player->acceleration.y = 0.1;
    vec2_add(&player->velocity, &player->acceleration);
    if (player->velocity.y > 2.0) {
        player->velocity.y = 2.0;
    }
    vec2_add(&player->position, &player->velocity);

    int x = player->position.x + 4;
    int y = player->position.y;
    int w = 16/2;
    int h = 16;
    
    player->collider = (SDL_Rect){x, y, w, h};

    int n = state->demons->size;

    for(int i = 0; i < n; i++){
        Demon* array = state->demons->array;
        Demon demon = array[i];

        if(!demon.alive){
            demon.sprite.x = 0;
            demon.sprite.y = 0;
            demon.sprite.w = 16;
            demon.sprite.h = 9;

            array[i] = demon;
            continue;
        }
        
        demon.acceleration.y = 0.1;
        
        
        if(demon.position.x - 8 > player->position.x){
            demon.velocity = (Vec2){-1, 0};

        }else if (demon.position.x + 8 < player->position.x){
            demon.velocity = (Vec2){1, 0};
        }else{
            y = demon.velocity.y;
            demon.velocity = (Vec2){0, y};
        }
        
        if(demon.position.y - 8 > player->position.y){
            demon.velocity = (Vec2){0, -1};

        }else if (demon.position.y + 8 < player->position.y){
            demon.velocity = (Vec2){0, 1};
        }else{
            x = demon.velocity.x;
            demon.velocity = (Vec2){x, 0};
        }

        if(!demon.velocity.x && !demon.velocity.y){
            demon.attack = true;
        }else{
            demon.attack = false;
        }

        if(demon.status == FROST){
            vec2_multiply(&demon.velocity, 0.5);
        }
        if(demon.status == BURN){
            demon.health -= 1;
        }
        
        vec2_add(&demon.velocity, &demon.acceleration);
        vec2_add(&demon.position, &demon.velocity);

        int x = demon.position.x + 4;
        int y = demon.position.y;
        int w = 16/2;
        int h = 16;

        demon.collider = (SDL_Rect){x, y, w, h};

        if(demon.health <= 0){
            demon.alive = false;
            state->deadDemons++;
        }

        array[i] = demon;

    }

    for(int i = 0; i < state->hailIndex; i++){
        Hail hail = state->hails[i];
        vec2_add(&hail.position, &hail.velocity);
        hail.collider.x = hail.position.x + 6;
        hail.collider.y = hail.position.y + 6;
        state->hails[i] = hail;

       // printf("Hail: %.2f, %.2f\n", hail.velocity.x, hail.velocity.y);
    }

    for(int i = 0; i < state->fireIndex; i++){
        Fire fire = state->fires[i];
        vec2_add(&fire.position, &fire.velocity);
        fire.collider.x = fire.position.x + 6;
        fire.collider.y = fire.position.y + 6;


        if(fire.count == 8){
            fire.count = 0;
            fire.frame += 1;
            if(fire.frame == 4){
                fire.frame = 0;
            }
        }

        fire.count += 1;
        fire.sprite.x = 16 * fire.frame;

        state->fires[i] = fire;

        //printf("Fire: %.2f, %.2f\n", fire.velocity.x, fire.velocity.y);
    }

    if(player->health <= 0){
        push(&gameStates, createGameOverState());
    }

    //printf("Player Velocity: %.2f, %.2f\n", player->velocity.x, player->velocity.y);

}

void handleCollisions(GameState* state){
    Player* player = state->player;
    
    int n = state->demons->size;

    // player - demon collision
    for(int i = 0; i < n; i++){
        Demon* array = state->demons->array;
        Demon demon = array[i];


        if(!demon.alive){
            continue;
        }

        if(SDL_HasIntersection(&player->collider, &demon.collider)){
            player->health -= 1000;//(int)demon.evil * 0.1; 
        }

    }

    // projectile - demon collision
    for(int i = 0; i < n; i++){
        Demon* array = state->demons->array;
        Demon demon = array[i];
        if(!demon.alive){
            continue;
        }

        for(int f = 0; f < state->fireIndex; f++){

            if(SDL_HasIntersection(&state->fires[f].collider, &demon.collider)){
                demon.health -= 20;
                demon.status = BURN;

                //effectively remove collider on hit
                state->fires[f].collider.x = 0;
                state->fires[f].collider.y = 0;
                state->fires[f].collider.w = 0;
                state->fires[f].collider.h = 0;
            }


        }

        for(int h = 0; h < state->hailIndex; h++){

            if(SDL_HasIntersection(&state->hails[h].collider, &demon.collider)){
                demon.health -= 20;
                demon.status = FROST;

                //effectively remove collider on hit
                state->hails[h].collider.x = 0;
                state->hails[h].collider.y = 0;
                state->hails[h].collider.w = 0;
                state->hails[h].collider.h = 0;
            }

        }

        array[i] = demon;


    }

    //entity map collision
    int c = state->map->total;
    Map* map = state->map;
    for(int i = 0; i < c; i++){
    if (SDL_HasIntersection(&player->collider, &map->colliders[i])) {  
        // Determine the depth of the intersection
        SDL_Rect intersection;
        SDL_IntersectRect(&player->collider, &map->colliders[i], &intersection);

        // Resolve collision by axis
        if (intersection.w < intersection.h) {
            // Horizontal collision
            if (player->velocity.x > 0) {
                player->position.x -= intersection.w; // Pushed from the right
            } else if (player->velocity.x < 0) {
                player->position.x += intersection.w; // Pushed from the left
            }
        } else {
            // Vertical collision
            if (player->velocity.y > 0) {
                player->position.y -= intersection.h; // Pushed from below
            } else if (player->velocity.y < 0) {
                player->position.y += intersection.h; // Pushed from above
            }
        }

        // Update collider to match the corrected position
        int x = player->position.x + 4;
        int y = player->position.y;
        int w = 16 / 2;
        int h = 16;

        player->collider = (SDL_Rect){x, y, w, h};
    }


        for(int j = 0; j < n; j++){
            Demon* array = state->demons->array;
            Demon demon = array[j];

            if(!demon.alive){
                continue;
            }

            if (SDL_HasIntersection(&map->colliders[i], &demon.collider)) {
                SDL_Rect intersection;
                SDL_IntersectRect(&demon.collider, &map->colliders[i], &intersection);

                // Resolve collision by axis
                if (intersection.w < intersection.h) {
                    // Horizontal collision
                    if (demon.velocity.x > 0) {
                        demon.position.x -= intersection.w; // Pushed from the right
                    } else if (demon.velocity.x < 0) {
                        demon.position.x += intersection.w; // Pushed from the left
                    }

                    Vec2 repulse;
                    if(player->position.y > demon.position.y){
                        repulse = (Vec2){0, 1};
                    }else{
                        repulse = (Vec2){0, -1};
                    }
                    vec2_add(&demon.position, &repulse);
                } else if(intersection.w < intersection.h){
                    // Vertical collision
                    if (demon.velocity.y > 0) {
                        demon.position.y -= intersection.h; // Pushed from below
                    } else if (demon.velocity.y < 0) {
                        demon.position.y += intersection.h; // Pushed from above
                    }

                    Vec2 repulse;
                    if(player->position.x > demon.position.x){
                        repulse = (Vec2){1, 0};
                    }else{
                        repulse = (Vec2){-1, 0};
                    }
                    vec2_add(&demon.position, &repulse);
                } else{
                    Vec2 repulse;
                    if(player->position.x > demon.position.x){
                        repulse = (Vec2){1, 0};
                    }else{
                        repulse = (Vec2){-1, 0};
                    }

                    // Resolve vertical collision
                    if (demon.velocity.y > 0) {
                        demon.position.y -= intersection.h;
                    } else if (demon.velocity.y < 0) {
                        demon.position.y += intersection.h;
                    }

                    vec2_add(&demon.position, &repulse);
                }

                // Update the demon's collider to match the new position
                int x = demon.position.x + 4;
                int y = demon.position.y;
                int w = 16 / 2;
                int h = 16;

                demon.collider = (SDL_Rect){x, y, w, h};

                // Update the demon in the array
                array[j] = demon;
            }

        }
    }
}

void updateCamera(GameState* state){
    Camera* camera = state->camera;
    SDL_Rect viewport;
    SDL_RenderGetViewport(renderer, &viewport);
    
    camera->position.x = (state->player->position.x  + 16 / 2) - viewport.w / 2;
    camera->position.y = (state->player->position.y  + 16 / 2) - viewport.h / 2;
    
    if(camera->position.x < 0){
      camera->position.x = 0;
    }
    if(camera->position.y < 0){
      camera->position.y = 0;
    }

    if(camera->position.x > MAP_WIDTH * 16 - viewport.w){
      camera->position.x = MAP_WIDTH * 16 - viewport.w;
    }

    if(camera->position.y > MAP_HEIGHT * 16 - viewport.h){
      camera->position.y = MAP_HEIGHT * 16 - viewport.h;
    }
}
