#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "../include/core/window.h"
#include "../include/core/renderer.h"
#include "../include/structures/stack.h"
#include "../include/core/render.h"
#include "../include/core/sprite.h"

SDL_Window* window;
SDL_Renderer* renderer;
Stack gameStates;

int main(){
    Uint32 timerStart;
    Uint32 timerEnd;
    float accumulatedSeconds = 0.0f;
    float cycleTime = 1.0f / 60.0f;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }
    if (TTF_Init() == -1) {
        SDL_Log("SDL_ttf could not initialize! TTF_Error: %s", TTF_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }


    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("Mix_OpenAudio Error: %s\n", Mix_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    window = initWindow();

    renderer = initRenderer(window);


    //initialize stack, push state onto stack
    initStack(&gameStates);

    GameState* current = peek(&gameStates);

    SDL_Texture* backgroundTexture = IMG_LoadTexture(renderer, "/assets/sprites/background.png");
    SDL_Texture* playTexture = IMG_LoadTexture(renderer, "/assets/sprites/play.png");

    current->textures[BACKGROUND] = backgroundTexture; 
    current->textures[PLAYBUTTON] = playTexture; 

    current->map = createMap("assets/map/map.png", "assets/map/map.txt");
    current->camera = createCamera();
    
    timerStart = SDL_GetTicks64();

    while (current->running) {
        timerEnd = SDL_GetTicks64();
        float elapsedSeconds = (timerEnd - timerStart) / 1000.0f;
        accumulatedSeconds += elapsedSeconds;

        timerStart = timerEnd;

        if(accumulatedSeconds > cycleTime){
            accumulatedSeconds -= cycleTime;


            current = peek(&gameStates);
        
            current->processInput(current);
            current->update(current);

        }
        current->render(current);
    }

    freeGameState(pop(&gameStates));

    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(playTexture);
    

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}