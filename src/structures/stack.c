#include "../../include/structures/stack.h"
#include "../../include/structures/gamestate.h"
#include <stdio.h>
#include <stdbool.h>

void initStack(Stack* stack){
    stack->top =-1;
    push(stack, createMenuState());
}

bool isEmpty(Stack* stack){
    return stack->top == -1;
}

bool push(Stack* stack, GameState* state){
    if(stack->top > MAX_SIZE){
        printf("Stack overflow\n");
        return false;
    }

    state->stack = stack;

    stack->data[++stack->top] = state;
    return true;
}

GameState* pop(Stack* stack){
    if(isEmpty(stack)){
        printf("Empty stack\n");
    }
    return stack->data[stack->top--];
}

GameState* peek(Stack* stack){
    if(isEmpty(stack)){
        printf("Empty stack\n");
        return NULL;
    }
    return stack->data[stack->top];
}