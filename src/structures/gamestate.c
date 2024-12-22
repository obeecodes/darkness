#include "../../include/structures/gamestate.h"
#include "../../include/core/input.h"
#include "../../include/core/renderer.h"
#include "../../include/core/update.h"
#include "../../include/core/render.h"
#include "../../include/core/sprite.h"
#include "../../include/entities/player.h"
#include "../../include/core/globals.h"
#include <SDL_image.h>

#include <stdlib.h>

GameState* createMenuState(){

    GameState* state = (GameState*)malloc(sizeof(GameState));

    if(state == NULL){
        printf("Memory allocation failed\n");
    }

    state->running = true;

    state->mouseClick = false;

    state->demons = NULL;

    state->processInput = menuStateInput;
    state->update = menuStateUpdate;
    state->render = menuStateRender;

    state->background.x = 0;
    state->background.y = 0;
    state->background.w = 200;
    state->background.y = 150;

    state->font = NULL;//TTF_OpenFont("/assets/fonts/pixel.ttf", 8);
    /*if(!(state->font)){
        printf("Failed to find font.\n");
        exit(1);
    }
    */
    return state;
}

GameState* createPlayState(){
    GameState* state = (GameState*)malloc(sizeof(GameState));

    if(state == NULL){
        printf("Memory allocation failed\n");
    }

    state->processInput = playStateInput;
    state->update = playStateUpdate;
    state->render = playStateRender;
    state->player = createPlayer();
    state->running = true;

    state->demons = createArrayList();
    state->deadDemons = 0;

    for(int i = 0; i < 3; i++)
        append(state->demons, createDemon());

    state->hailIndex = 0;
    state->fireIndex = 0;

    state->font = TTF_OpenFont("/assets/fonts/Hack_Regular_Nerd_Font_Complete_Mono.ttf", 8);

    if(!(state->font)){
        printf("Failed to find font.\n");
        exit(1);
    }



    SDL_Texture* playerTexture = IMG_LoadTexture(renderer, "/assets/sprites/player.png");
    SDL_Texture* demonTexture = IMG_LoadTexture(renderer, "/assets/sprites/demon.png");

    state->textures[PLAYER] = playerTexture; 
    state->textures[DEMON] = demonTexture; 

    state->map = createMap("assets/map/map.png", "assets/map/map.txt");
    state->camera = createCamera();
    
    return state;
}

GameState* createPauseState(){

    GameState* state = (GameState*)malloc(sizeof(GameState));

    if(state == NULL){
        printf("Memory allocation failed\n");
    }

    state->running = true;

    state->mouseClick = false;

    state->demons = NULL;

    state->processInput = pauseStateInput;
    state->update = pauseStateUpdate;
    state->render = pauseStateRender;

    SDL_Texture* pause = IMG_LoadTexture(renderer, "/assets/sprites/pause.png");

    state->textures[PAUSESCREEN] = pause; 

    state->font = NULL;//TTF_OpenFont("/assets/fonts/pixel.ttf", 8);
    /*if(!(state->font)){
        printf("Failed to find font.\n");
        exit(1);
    }
    */
    return state;;
}

GameState* createGameOverState(){

    GameState* state = (GameState*)malloc(sizeof(GameState));

    if(state == NULL){
        printf("Memory allocation failed\n");
    }

    state->running = true;

    state->mouseClick = false;

    state->demons = NULL;

    state->processInput = gameOverStateInput;
    state->update = gameOverStateUpdate;
    state->render = gameOverStateRender;
    
    SDL_Texture* gameOver = IMG_LoadTexture(renderer, "/assets/sprites/gameOver.png");

    state->textures[GAMEOVERSCREEN] = gameOver; 

    state->font = NULL;//TTF_OpenFont("/assets/fonts/pixel.ttf", 8);
    /*if(!(state->font)){
        printf("Failed to find font.\n");
        exit(1);
    }
    */
    return state;;
}

/*
GameState* createGameOverState(){

    GameState* state = (GameState*)malloc(sizeof(GameState));

    if(state == NULL){
        printf("Memory allocation failed\n");
    }



    state->demons = createArrayList();
        
    state->processInput = gameOverStateInput;
    state->update = gameOverStateUpdate;
    state->render = gameOverStateRender;

    state->font = TTF_OpenFont("/assets/fonts/Hack_Regular_Nerd_Font_Complete_Mono.ttf", 8);
    if(!(state->font)){
        printf("Failed to find font.\n");
        exit(1);
    }
    return state;
}
*/
void freeGameState(GameState* state){
    free(state->player);
    freeArrayList(state->demons);
    TTF_CloseFont(state->font);
    free(state);

}

