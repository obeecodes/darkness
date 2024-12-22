#pragma once

#include <SDL2/SDL.h>
#include "camera.h"

// Tile size
#define TILE_WIDTH 16
#define TILE_HEIGHT 16

// Map dimensions (adjust as needed)
#define MAP_WIDTH 20
#define MAP_HEIGHT 10

// Tile types
#define TILE_EMPTY 0
#define TILE_GROUND 1
#define TILE_PLATFORM 2

typedef struct {
    int tiles[MAP_HEIGHT][MAP_WIDTH]; // 2D array for the map layout
    SDL_Texture* tileset;            // Texture for rendering tiles
    SDL_Rect colliders[50];
    int total;
} Map;

// Function prototypes
Map* createMap(const char* tilesetPath, const char* mapFilePath);
void renderMap(Map* map, Camera* camera);
void destroyMap(Map* map);
