//
// Created by chris on 13/08/2017.
//

#ifndef MINECRAFT_CLONE_FIRSTPERSONCONTROLLER_H
#define MINECRAFT_CLONE_FIRSTPERSONCONTROLLER_H


#include "Camera.h"

enum DIRECTION
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class FirstPersonController {
public:


    // Moves the controller by specified amount
    void move(glm::vec3 amount);
    void move(DIRECTION direction, float distance);


    // Rotates the controller's view by specified amount
    void rotate(float yaw, float pitch);

    // Returns the combined view and projection matrix
    glm::mat4 getCombinedMatrix();



    /*
     * Getters and setters
     */

    const glm::vec3& getPosition() const;
    void setPosition(const glm::vec3& position);

    const glm::vec3& getDirection() const;
    void setDirection(const glm::vec3& direction);


    void setCameraAspect(float aspect);

private:

    // Position of the controller
    glm::vec3 position = glm::vec3(0, 0, 0);

    // Direction the controller is facing
    glm::vec3 direction = glm::vec3(0, 0, -1);


    // Stores controller's view
    Camera camera;

    // Camera variables
    float camera_fov = 70;
    float camera_aspect = 1;
    float camera_near = 0.01;
    float camera_far = 1000.f;

    float camera_yaw = 0.0f;
    float camera_pitch = 0.0f;
    bool usingEulerAngles = true;

    // Determines if the matrices are out-of-date
    bool cameraNeedsUpdate = true;

    // Updates the camera's matrices
    void updateCamera();

    glm::vec3 getRight();
};


#endif //MINECRAFT_CLONE_FIRSTPERSONCONTROLLER_H
