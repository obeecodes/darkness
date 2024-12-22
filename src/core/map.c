#include "../../include/core/map.h"
#include "../../include/core/renderer.h"
#include "../../include/core/globals.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

// Create and initialize a map
Map* createMap(const char* tilesetPath, const char* mapFilePath) {
    // Allocate memory for the map
    Map* map = (Map*)malloc(sizeof(Map));
    if (!map) {
        printf("Failed to allocate memory for map.\n");
        exit(1);
    }

    // Load map layout from file
    FILE* file = fopen(mapFilePath, "r");
    if (!file) {
        printf("Failed to open map file: %s\n", mapFilePath);
        free(map);
        exit(1);
    }

    SDL_Rect collider;
    collider.w = TILE_WIDTH;
    collider.h = TILE_HEIGHT;
    int c = 0;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            fscanf(file, "%d", &map->tiles[y][x]);

            if(x == 0 && y == 0){
                
            }

            if(map->tiles[y][x] == TILE_GROUND){
                collider.x = x * TILE_WIDTH;
                collider.y = y * TILE_HEIGHT;
                map->colliders[c] = collider;
                c++;
            }

            if(map->tiles[y][x] == TILE_PLATFORM){
                collider.x = x * TILE_WIDTH;
                collider.y = y * TILE_HEIGHT + 8;
                collider.h = 8;
                map->colliders[c] = collider;
                c++;
                collider.h = TILE_HEIGHT;
            }
        }
    }

    // create side barriers
    SDL_Rect Lbarrier;
    Lbarrier.x = -2 * TILE_WIDTH + 1;
    Lbarrier.y = 0;
    Lbarrier.w = 2 * 16;
    Lbarrier.h = 10 * 16;
    map->colliders[c] = Lbarrier;
    c++;

    SDL_Rect Rbarrier;
    Rbarrier.x = 20 * TILE_WIDTH - 1;
    Rbarrier.y = 0;
    Rbarrier.w = 2 * 16;
    Rbarrier.h = 10 * 16;
    map->colliders[c] = Rbarrier;
    c++;

    map->total = c;


    
    fclose(file);

    // Load tileset texture
    SDL_Texture* mapTiles = IMG_LoadTexture(renderer, tilesetPath);
    if (!mapTiles) {
        printf("Failed to load tileset: %s\n", SDL_GetError());
        free(map);
        exit(1);
    }


    map->tileset = mapTiles;

    return map;
}

// Render the map
void renderMap(Map* map, Camera* camera) {
    SDL_Rect srcRect, destRect;
    srcRect.w = TILE_WIDTH;
    srcRect.h = TILE_HEIGHT;
    destRect.w = TILE_WIDTH;
    destRect.h = TILE_HEIGHT;

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {
            int tileType = map->tiles[y][x];
            //printf("%d ", tileType);
            //if (tileType == TILE_EMPTY) continue;

            // Set source rectangle based on tile type
            srcRect.x = tileType * TILE_WIDTH;
            srcRect.y = 0;

            // Set destination rectangle for rendering
            if(tileType == TILE_PLATFORM){
                SDL_Rect dst;
                dst.x = x * TILE_WIDTH - camera->position.x;
                dst.y = y * TILE_HEIGHT+8 - camera->position.y;
                dst.w = 16;
                dst.h = 8;

                SDL_RenderCopy(renderer, map->tileset, &srcRect, &dst);
                continue;
            }
            destRect.x = x * TILE_WIDTH - camera->position.x;
            destRect.y = y * TILE_HEIGHT - camera->position.y;

            SDL_RenderCopy(renderer, map->tileset, &srcRect, &destRect);

        }
        //printf("\n");
    }

    SDL_Rect tmp;
    tmp.h = TILE_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 255, 10, 15, 255);

    for(int i = 0; i < map->total; i++){
        tmp.x = map->colliders[i].x - camera->position.x;
        tmp.y = map->colliders[i].y - camera->position.y;
        tmp.w = map->colliders[i].w;
        tmp.h = map->colliders[i].h;

        //SDL_RenderDrawRect(renderer, &tmp);  
    }
}

// Free resources allocated by the map
void destroyMap(Map* map) {
    if (map) {
        if (map->tileset) {
            SDL_DestroyTexture(map->tileset);
        }
        free(map);
    }
}