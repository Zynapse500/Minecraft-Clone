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

    // Removes a block at coordinates
    void removeBlock(int x, int y, int z);

    // Places a block at coordinates
    void placeBlock(int x, int y, int z, unsigned type);

    // Casts a ray and returns first intersecting block-coordinates
    // Returns (y = -1) if no block was found
    glm::ivec3 getRayBlockIntersection(glm::vec3 rayOrigin, glm::vec3 ray);

private:

    std::map<std::pair<int, int>, Chunk> chunks;


    // Returns the chunk that contains specified block coordinates
    Chunk *getChunk(int x, int z);
};


#endif //MINECRAFT_CLONE_WORLD_H
