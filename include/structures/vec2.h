#pragma once

typedef struct Vec2{
    float x;
    float y;
} Vec2;

void vec2_add(Vec2* v1, Vec2* v2);

void vec2_multiply(Vec2* v, float c);

void vec2_normalize(Vec2* v);

Vec2 vec2_to_from(Vec2* a, Vec2* b);