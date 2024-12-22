#pragma once

#include "../structures/gamestate.h"

void menuStateUpdate(GameState* state);

void playStateUpdate(GameState* state);
void updatePositions(GameState* state);
void updateCamera(GameState* state);
void handleCollisions(GameState* state);

void pauseStateUpdate(GameState* state);

void gameOverStateUpdate(GameState* state);


