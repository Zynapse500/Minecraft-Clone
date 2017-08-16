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

    auto pairToString = [](std::pair<int, int> &pair) {
        return "(" + std::to_string(pair.first) + ", " + std::to_string(pair.second) + ")";
    };

    int x = 0, y = 0;
    int dx = 0, dy = -1;

    int r = 20;

    for (int i = 0; i < r * r; ++i) {

        auto currentChunk = std::make_pair(chunkPosition.x + x, chunkPosition.y + y);

        if (chunks.find(currentChunk) == chunks.end()) {

            Chunk &createdChunk = chunks[currentChunk];

            glm::ivec2 neighborDirections[] = {
                    glm::ivec2(1, 0),
                    glm::ivec2(-1, 0),
                    glm::ivec2(0, 1),
                    glm::ivec2(0, -1)
            };

            for (auto &neighborDirection : neighborDirections) {
                auto neighborPosition = std::make_pair(currentChunk.first + neighborDirection.x,
                                                       currentChunk.second + neighborDirection.y);
                auto neighbor = chunks.find(neighborPosition);

                if (neighbor != chunks.end()) {
                    Chunk &neighborChunk = (*neighbor).second;
                    neighborChunk.setNeighbor(&createdChunk, -neighborDirection.x, -neighborDirection.y);
                    createdChunk.setNeighbor(&neighborChunk, neighborDirection.x, neighborDirection.y);
                }
            }

            createdChunk.generate(currentChunk.first, currentChunk.second);
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

glm::ivec3 World::getRayBlockIntersection(glm::vec3 rayOrigin, glm::vec3 ray) {
    const float distance = 5;

    glm::ivec3 blockStart = rayOrigin;
    glm::ivec3 blockEnd = rayOrigin + distance * ray;

    int stepXY = (abs(blockEnd.y - blockStart.y) > abs(blockEnd.x - blockStart.x));
    if(stepXY) {
        std::swap(blockStart.x, blockStart.y);
        std::swap(blockEnd.x, blockEnd.y);
    }

    int stepXZ = (abs(blockEnd.z - blockStart.z) > abs(blockEnd.x - blockStart.x));
    if(stepXZ) {
        std::swap(blockStart.x, blockStart.z);
        std::swap(blockEnd.x, blockEnd.z);
    }

    glm::ivec3 delta = glm::abs(blockEnd - blockStart);

    float errorXY = delta.x / 2.f;
    float errorXZ = delta.x / 2.f;

    glm::ivec3 step {
            blockStart.x > blockEnd.x ? -1 : 1,
            blockStart.y > blockEnd.y ? -1 : 1,
            blockStart.z > blockEnd.z ? -1 : 1
    };

    int y = blockStart.y;
    int z = blockStart.z;

    for (int x = blockStart.x; x < blockEnd.x; x += step.x) {
        glm::ivec3 point(x, y, z);

        if(stepXZ)
            std::swap(point.x, point.z);
        if(stepXY)
            std::swap(point.x, point.y);



        // Use point
        std::cout << glm::to_string(point) << std::endl;
        removeBlock(point.x, point.y, point.z);


        errorXY -= delta.y;
        errorXZ -= delta.z;

        if(errorXY < 0) {
            y += step.y;
            errorXY += delta.x;
        }
        if(errorXZ < 0) {
            z += step.z;
            errorXZ += delta.x;
        }
    }


    return glm::ivec3();
}

void World::removeBlock(int x, int y, int z) {

    auto chunkPosition = std::make_pair<int, int>(int(floorf(x / 16.f)),
                                                  int(floorf(z / 16.f)));

    auto chunkIterator = chunks.find(chunkPosition);
    if (chunkIterator != chunks.end()) {
        (*chunkIterator).second.removeBlock(x, y, z);
    }
}
