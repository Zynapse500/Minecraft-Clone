//
// Created by chris on 13/08/2017.
//

#include "FirstPersonController.h"

glm::mat4 FirstPersonController::getCombinedMatrix() {
    if(this->cameraNeedsUpdate)
        updateCamera();

    return camera.projectionMatrix * camera.viewMatrix;
}

void FirstPersonController::updateCamera() {
    this->camera.projectionMatrix = glm::perspective(glm::radians(this->camera_fov), this->camera_aspect, this->camera_near, this->camera_far);
    this->camera.viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));

    cameraNeedsUpdate = false;
}

void FirstPersonController::move(glm::vec3 amount) {
    position += amount;

    cameraNeedsUpdate = true;
}

const glm::vec3 &FirstPersonController::getPosition() const {
    return position;
}

void FirstPersonController::setPosition(const glm::vec3 &position) {
    FirstPersonController::position = position;

    cameraNeedsUpdate = true;
}

const glm::vec3 &FirstPersonController::getDirection() const {
    return direction;
}

void FirstPersonController::setDirection(const glm::vec3 &direction) {
    FirstPersonController::direction = direction;

    cameraNeedsUpdate = true;
}

void FirstPersonController::setCameraAspect(float aspect) {
    this->camera_aspect = aspect;

    cameraNeedsUpdate = true;
}
