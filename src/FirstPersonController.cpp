//
// Created by chris on 13/08/2017.
//

#include <iostream>
#include "FirstPersonController.h"

glm::mat4 FirstPersonController::getCombinedMatrix() {
    if (this->cameraNeedsUpdate)
        updateCamera();

    return camera.projectionMatrix * camera.viewMatrix;
}

void FirstPersonController::updateCamera() {
    this->camera.projectionMatrix = glm::perspective(glm::radians(this->camera_fov), this->camera_aspect,
                                                     this->camera_near, this->camera_far);

    if (usingEulerAngles) {
        direction.x = cosf(camera_yaw) * cosf(camera_pitch);
        direction.y = sinf(camera_pitch);
        direction.z = sinf(camera_yaw) * cosf(camera_pitch);
    }

    this->camera.viewMatrix = glm::lookAt(position, position + direction, glm::vec3(0, 1, 0));

    cameraNeedsUpdate = false;
}

void FirstPersonController::move(glm::vec3 amount) {
    position += amount;

    cameraNeedsUpdate = true;
}

const glm::vec3& FirstPersonController::getPosition() const {
    return position;
}

void FirstPersonController::setPosition(const glm::vec3& position) {
    FirstPersonController::position = position;

    cameraNeedsUpdate = true;
}

const glm::vec3& FirstPersonController::getDirection() const {
    return direction;
}

void FirstPersonController::setDirection(const glm::vec3& direction) {
    FirstPersonController::direction = direction;

    cameraNeedsUpdate = true;
}

void FirstPersonController::setCameraAspect(float aspect) {
    this->camera_aspect = aspect;

    cameraNeedsUpdate = true;
}

void FirstPersonController::move(DIRECTION direction, float distance) {
    switch (direction) {
        case FORWARD: {
            glm::vec3 forward = glm::normalize(glm::cross(glm::vec3(0, 1, 0), getRight()));
            move(forward * distance);
        }
            break;

        case BACKWARD: {
            glm::vec3 backward = glm::normalize(glm::cross(getRight(), glm::vec3(0, 1, 0)));
            move(backward * distance);
        }
            break;

        case RIGHT:
            move(this->getRight() * distance);
            break;

        case LEFT:
            move(this->getRight() * -distance);
            break;

        case UP:
            move(glm::vec3(0, distance, 0));
            break;

        case DOWN:
            move(glm::vec3(0, -distance, 0));
            break;
    }
}

glm::vec3 FirstPersonController::getRight() {
    return glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
}

void FirstPersonController::rotate(float yaw, float pitch) {
    camera_yaw += yaw;
    camera_pitch += pitch;

    camera_pitch = glm::clamp(camera_pitch, -1.55f, 1.55f);

    if (camera_yaw > TWO_PI) {
        camera_yaw -= TWO_PI;
    } else if (camera_yaw < -TWO_PI) {
        camera_yaw += TWO_PI;
    }

    cameraNeedsUpdate = true;
}
