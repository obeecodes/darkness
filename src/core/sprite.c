#include "../../include/core/sprite.h"

void updateSprite(GameState* state){
    Player* player = state->player;

    int n = state->demons->size;

    for(int i = 0; i < n; i++){


        if(!state->demons->array[i].alive){
            continue;
        }
        state->demons->array[i].counter += 1;
        state->demons->array[i].run += 1;

        if(state->demons->array[i].position.x > player->position.x){
            state->demons->array[i].sprite.y = 16 * 1;
        }else{
            state->demons->array[i].sprite.y = 16 * 0;
        }

        if(state->demons->array[i].attack){
            if(state->demons->array[i].counter % 15 == 0){

                if(state->demons->array[i].sprite.x == 16 * 2){
                    state->demons->array[i].sprite.x = 16 * 3;
                } else{
                    state->demons->array[i].sprite.x = 16 * 2;
                }

                state->demons->array[i].counter = 0;

            }
        }else{
            if(state->demons->array[i].run % 15 == 0){

                if(state->demons->array[i].sprite.x == 16 * 0){
                    state->demons->array[i].sprite.x = 16 * 1;
                } else{
                    state->demons->array[i].sprite.x = 16 * 0;
                }

                state->demons->array[i].run = 0;

            }
        }


    }

    if(player->state == RUNNING){
        player->counter += 1;

        if(player->velocity.x < 0){
            player->sprite.y = 16 * 3;
        }else{
            player->sprite.y = 16 * 1;
        }

        if(player->counter % 10 == 0){

            if(player->sprite.x == 16 * 0){
                player->sprite.x = 16 * 1;
            }else if (player->sprite.x == 16 * 1){
                player->sprite.x = 16 * 2;
            }else{
                player->sprite.x = 16 * 0;
            }

            player->counter = 0;
        }

    }

    if(player->state == IDLE){
        player->sprite.x = 0;
        if(player->sprite.y == 16 * 1){
            player->sprite.y = 0;
        }else if (player->sprite.y == 16 * 3){
            player->sprite.y = 16 * 2;
        }

    }

    
}