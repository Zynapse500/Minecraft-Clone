//
// Created by chris on 13/08/2017.
//

#ifndef MINECRAFT_CLONE_FIRSTPERSONCONTROLLER_H
#define MINECRAFT_CLONE_FIRSTPERSONCONTROLLER_H


#include "Camera.h"

class FirstPersonController {
public:


    // Moves the controller by specified amount
    void move(glm::vec3 amount);

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
    glm::vec3 position;

    // Direction the controller is facing
    glm::vec3 direction;


    // Stores controller's view
    Camera camera;

    // Camera variables
    float camera_fov = 70;
    float camera_aspect = 1;
    float camera_near = 0.01;
    float camera_far = 100.f;

    // Determines if the matrices are out-of-date
    bool cameraNeedsUpdate = true;

    // Updates the camera's matrices
    void updateCamera();

};


#endif //MINECRAFT_CLONE_FIRSTPERSONCONTROLLER_H
