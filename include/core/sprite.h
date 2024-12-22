#pragma once
#include "../structures/gamestate.h"

#include <SDL.h>

typedef enum {
    PLAYER,
    DEMON,
    UI,
    WORLD,
    BACKGROUND,
    PLAYBUTTON,
    PAUSESCREEN,
    GAMEOVERSCREEN
} TextureTag;

void updateSprite(GameState* state);