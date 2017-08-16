//
// Created by chris on 15/08/2017.
//

#ifndef MINECRAFT_CLONE_WORLD_H
#define MINECRAFT_CLONE_WORLD_H


#include <map>
#include "Chunk.h"

class World {

public:

    // Generates the world
    void generate();

    // Updates the world based on where the player is
    void update(glm::vec3 playerPosition);

    // Renders the world based on where the player is
    void draw(glm::vec3 playerPosition);


    void removeBlock(int x, int y, int z);

    // Casts a ray and returns first intersecting block-coordinates
    glm::ivec3 getRayBlockIntersection(glm::vec3 rayOrigin, glm::vec3 ray);

private:

    std::map<std::pair<int, int>, Chunk> chunks;
};


#endif //MINECRAFT_CLONE_WORLD_H
