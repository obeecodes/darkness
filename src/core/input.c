#include <SDL.h>
#include "../../include/core/input.h"
#include "../../include/core/globals.h"
#include "../../include/core/renderer.h"
#include "../../include/structures/stack.h"
#include <stdio.h>

void playStateInput(GameState* state) {
    SDL_Event event;
    Player* player = state->player;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state->running = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                        if(!(player->state == JUMPING)){
                            player->velocity.y = -2.0f * 2;
                            player->sprite.x = 16 * 1;
                            player->state = JUMPING;
                        }
                        break;
                    case SDL_SCANCODE_S:
                        player->velocity.y = 2.0f;
                        player->sprite.x = 16 * 3;
                        player->state = PRAYING;
                        break;
                    case SDL_SCANCODE_A:
                        if(player->state == RUNNING){
                            break;
                        }
                        player->velocity.x = -2.0f;
                        player->sprite.x = 16 * 0;
                        player->sprite.y = 16 * 3;
                        player->state = RUNNING;
                        player->right = false;
                        break;
                    case SDL_SCANCODE_D:
                        if(player->state == RUNNING){
                            break;
                        }
                        player->velocity.x = 2.0f;
                        player->sprite.x = 16 * 0;
                        player->sprite.y = 16 * 1;
                        player->state = RUNNING;
                        player->right = true;

                        break;
                    case SDL_SCANCODE_J:
                        player->sprite.x = 16 * 2;
                        player->state = ATTACKING;

                        break;
                    case SDL_SCANCODE_K:
                        if(!player->fireToIce){
                            state->hails[state->hailIndex++] = createHail(player->position, player->right);
                            if(state->hailIndex > MAX_HAIL - 1){
                                state->hailIndex = 0;
                            }
                        }else{
                            state->fires[state->fireIndex++] = createFire(player->position, player->right);

                            if(state->fireIndex > MAX_FIRE - 1){
                                state->fireIndex = 0;
                            }
                        }


                        break;
                    case SDL_SCANCODE_I:
                        player->fireToIce = !player->fireToIce;

                        break;
                    case SDL_SCANCODE_ESCAPE:
                        state->running = SDL_FALSE;
                        break;
                    case SDL_SCANCODE_P:
                        push(&gameStates, createPauseState());

                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                        player->velocity.y = 0.0f;
                        player->state = IDLE;

                        break;
                    case SDL_SCANCODE_S:
                        player->velocity.y = 0.0f;
                        player->state = IDLE;

                        break;
                    case SDL_SCANCODE_A:
                        player->velocity.x = 0.0f;
                        player->state = IDLE;

                        break;
                    case SDL_SCANCODE_D:
                        player->velocity.x = 0.0f;
                        player->state = IDLE;

                        break;
                    case SDL_SCANCODE_J:
                        player->sprite.x = 16 * 0;
                        player->state = IDLE;

                        break;
                    case SDL_SCANCODE_K:
                        player->sprite.x = 16 * 0;
                        player->state = IDLE;


                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
                    SDL_RenderSetScale(renderer, 8, 8);
                    SDL_RenderSetViewport(renderer, NULL);
                }
                break;
            default:
                break;
        }
    }
}

void menuStateInput(GameState* state){
    SDL_Event event;
    Player* player = state->player;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state->running = SDL_FALSE;
                break;
            case SDL_MOUSEMOTION:
                state->mousePosX = event.motion.x;
                state->mousePosY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    state->mouseClick = true;
                }
                break; 
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT){
                    state->mouseClick = false;
                }
                break; 
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        state->running = SDL_FALSE;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                        player->velocity.y = 0.0f;
                        player->state = IDLE;

                        break;

                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
                    SDL_RenderSetScale(renderer, 8, 8);
                    SDL_RenderSetViewport(renderer, NULL);
                }
                break;
                default:
                    break;
        }
    }
}

void pauseStateInput(GameState* state){
    SDL_Event event;
    Player* player = state->player;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state->running = SDL_FALSE;
                break;
            case SDL_MOUSEMOTION:
                state->mousePosX = event.motion.x;
                state->mousePosY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    state->mouseClick = true;
                }
                break; 
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT){
                    state->mouseClick = false;
                }
                break; 
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        state->running = SDL_FALSE;
                        break;
                    case SDL_SCANCODE_P:
                        pop(state->stack);
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                        player->velocity.y = 0.0f;
                        player->state = IDLE;

                        break;

                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
                    SDL_RenderSetScale(renderer, 8, 8);
                    SDL_RenderSetViewport(renderer, NULL);
                }
                break;
                default:
                    break;
        }
    }
}

void gameOverStateInput(GameState* state){
    SDL_Event event;
    Player* player = state->player;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                state->running = SDL_FALSE;
                break;
            case SDL_MOUSEMOTION:
                state->mousePosX = event.motion.x;
                state->mousePosY = event.motion.y;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT){
                    state->mouseClick = true;
                }
                break; 
            case SDL_MOUSEBUTTONUP:
                if(event.button.button == SDL_BUTTON_LEFT){
                    state->mouseClick = false;
                }
                break; 
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_RETURN:
                        state->running = SDL_FALSE;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_W:
                        player->velocity.y = 0.0f;
                        player->state = IDLE;

                        break;

                        break;
                    default:
                        break;
                }
                break;
            case SDL_WINDOWEVENT:
                if(event.window.event == SDL_WINDOWEVENT_RESIZED){
                    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
                    SDL_RenderSetScale(renderer, 8, 8);
                    SDL_RenderSetViewport(renderer, NULL);
                }
                break;
                default:
                    break;
        }
    }
}