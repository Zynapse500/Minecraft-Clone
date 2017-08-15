//
// Created by chris on 15/08/2017.
//

#include <iostream>
#include "World.h"

void World::generate() {
    for (int x = 0; x < 4; ++x) {
        for (int z = 0; z < 4; ++z) {
            printf("Generating chunk (%d, %d)\n", x, z);
            chunks[std::make_pair(x, z)].generate(16 * x, 16 * z);
        }
    }
}

void World::update(glm::vec3 playerPosition) {

}

void World::draw(glm::vec3 playerPosition) {
    for (auto& chunk : chunks) {
        chunk.second.draw();
    }
}
