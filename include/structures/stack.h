#pragma once

//#include "gamestate.h"
#include <stdbool.h>

#define MAX_SIZE 5

typedef struct GameState GameState;

typedef struct Stack Stack;

struct Stack{
    GameState* data[MAX_SIZE];
    int top;

    Stack* stack;
};

void initStack(Stack* stack);

bool isEmpty(Stack* stack);

bool push(Stack* stack, GameState* state);

GameState* pop(Stack* stack);

GameState* peek(Stack* stack);