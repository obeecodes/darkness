#pragma once

#include "../structures/vec2.h"

typedef struct Camera{
    Vec2 position;
    Vec2 dimension;
} Camera;

Camera* createCamera();