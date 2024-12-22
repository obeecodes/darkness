#include <SDL.h>
#include "../../include/core/renderer.h"
#include "../../include/core/globals.h"

SDL_Renderer* initRenderer(SDL_Window* window){

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_RenderSetLogicalSize(renderer, 512, 288);
    SDL_RenderSetIntegerScale(renderer, SDL_TRUE);
    SDL_RenderSetScale(renderer, 8, 8);
    SDL_RenderSetViewport(renderer, NULL);

    return renderer;
}