#include "../../include/core/camera.h"
#include <stdlib.h>

Camera* createCamera(){
    Camera* camera = (Camera*)malloc(sizeof(Camera));
    camera->position = (Vec2){0, 0};
    camera->position = (Vec2){0, 0};
    return camera;
}