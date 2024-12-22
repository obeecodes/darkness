#pragma once

#include "../entities/demon.h"

typedef struct ArrayList {
    Demon* array;
    int size;
    int capacity;
} ArrayList;

ArrayList* createArrayList();

void append(ArrayList* list, Demon demon);

void freeArrayList(ArrayList* list);