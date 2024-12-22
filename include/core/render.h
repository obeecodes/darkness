#pragma once

#include <SDL.h>

#include "../structures/gamestate.h"

void menuStateRender(GameState* state);



void playStateRender(GameState* state);

void renderEntities(GameState* state);
void renderProjectiles(GameState* state);
void renderHUD(GameState* state);

void pauseStateRender(GameState* state);
void gameOverStateRender(GameState* state);
