#include "../../include/structures/arraylist.h"
#include <stdlib.h>

ArrayList* createArrayList(){
    ArrayList* list = (ArrayList*)malloc(sizeof(ArrayList));
    list->size = 0;
    list->capacity = 4;
    list->array = malloc(list->capacity * sizeof(Demon));

    return list;
}

void append(ArrayList* list, Demon demon){
    if(list->size == list->capacity){
        list->capacity *= 2;
        list->array = realloc(list->array, list->capacity * sizeof(Demon));
    }

    list->array[list->size++] = demon;
}

void freeArrayList(ArrayList* list){
    free(list->array);
    free(list);
}