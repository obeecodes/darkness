#pragma once

#include <SDL.h>
#include "../entities/player.h"
#include "../structures/arraylist.h"
#include "../structures/vec2.h"
#include "../core/map.h"
#include "../core/camera.h"
#include "../entities/hail.h"
#include "../entities/fire.h"
#include <SDL_ttf.h>

#include <stdbool.h>

#define MAX_TEXTURES 10
#define MAX_HAIL 100
#define MAX_FIRE 100

typedef struct Stack Stack;
typedef struct GameState GameState;

typedef enum {
    MAINMENU,
    PLAY,
    PAUSE,
    SETTINGS,
    GAMEOVER
} GameStateTag;


typedef struct GameState{
    void (*init)();
    void (*processInput)(GameState* state);
    void (*update)(GameState* state);
    void (*render)(GameState* state);

    Player* player;
    ArrayList* demons;

    SDL_Texture* textures[MAX_TEXTURES];

    Map* map;

    Camera* camera;

    bool running;

    Hail hails[MAX_HAIL];
    int hailIndex;

    Fire fires[MAX_FIRE];
    int fireIndex;

    TTF_Font* font;
    int deadDemons;

    int mousePosX;
    int mousePosY;
    bool mouseClick;

    SDL_Rect button;

    SDL_Rect background;   

    Stack* stack;    

} GameState;


GameState* createMenuState();
GameState* createPlayState();
GameState* createPauseState();
GameState* createGameOverState();

void freeGameState(GameState* state);