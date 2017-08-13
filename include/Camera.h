//
// Created by chris on 13/08/2017.
//

#ifndef MINECRAFT_CLONE_CAMERA_H
#define MINECRAFT_CLONE_CAMERA_H


#include "Batch/glm.h"

struct Camera {
    glm::mat4 projectionMatrix = glm::mat4();
    glm::mat4 viewMatrix = glm::mat4();
};


#endif //MINECRAFT_CLONE_CAMERA_H
