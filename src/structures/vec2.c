#include "../../include/structures/vec2.h"
#include <math.h>

void vec2_add(Vec2* v1, Vec2* v2){
    v1->x += v2->x;
    v1->y += v2->y;
}

void vec2_multiply(Vec2* v, float c){
    v->x *= c;
}

void vec2_normalize(Vec2* v){
    float length = sqrt(v->x * v->x + v->y * v->y);

    if(length != 0){
        v->x /= length;
        v->y /= length;
    }
}

Vec2 vec2_to_from(Vec2* a, Vec2* b){
    Vec2 v;
    v.x = a->x - b->x;
    v.y = a->y - b->y;

    return v;
}