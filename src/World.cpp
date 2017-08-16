//
// Created by chris on 15/08/2017.
//

#include <iostream>
#include "World.h"

void World::generate() {
    /*for (int x = 0; x < 4; ++x) {
        for (int z = 0; z < 4; ++z) {
            chunks[std::make_pair(x, z)].generate(16 * x, 16 * z);
        }
    }*/
}

void World::update(glm::vec3 playerPosition) {
    // Find the chunk closest to the player that is still not generated
    // within a 5-chunk radius
    glm::ivec2 chunkPosition;
    chunkPosition.x = int(floorf(playerPosition.x / 16));
    chunkPosition.y = int(floorf(playerPosition.z / 16));

    auto pairToString = [](std::pair<int, int> pair) {
        return "(" + std::to_string(pair.first) + ", " + std::to_string(pair.second) + ")";
    };

    int x = 0, y = 0;
    int dx = 0, dy = -1;

    int r = 20;

    for (int i = 0; i < r * r; ++i) {

        auto pair = std::make_pair(chunkPosition.x + x, chunkPosition.y + y);

        if(chunks.find(pair) == chunks.end())
        {
            chunks[pair].generate(pair.first, pair.second);
            break;
        }

        if (x == y || (x < 0 && x == -y) ||
            (x > 0 && x == 1 - y)) {
            auto tmp = dx;
            dx = -dy, dy = tmp;
        }
        x += dx, y += dy;
    }
}

void World::draw(glm::vec3 playerPosition) {
    for (auto &chunk : chunks) {
        chunk.second.draw();
    }
}
