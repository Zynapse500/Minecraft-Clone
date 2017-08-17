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

    glm::vec3 rayStart = rayOrigin;
    glm::vec3 rayEnd = rayOrigin + distance * ray;

    glm::vec3 delta = glm::abs(rayEnd - rayStart);
    glm::vec3 dt_delta = 1.0f / delta;

    float t = 0;

    glm::ivec3 currentBlock = glm::floor(rayStart);

    int n = 1;
    glm::ivec3 increment;
    glm::vec3 t_next;

    for (int i = 0; i < 3; ++i) {
        if (delta[i] == 0) {
            increment[i] = 0;
            t_next[i] = dt_delta[i];
        } else if (rayEnd[i] > rayStart[i]) {
            increment[i] = 1;
            n += int(floor(rayEnd[i])) - currentBlock[i];
            t_next[i] = (floorf(rayStart[i]) + 1 - rayStart[i]) * dt_delta[i];
        } else {
            increment[i] = -1;
            n += currentBlock[i] - int(floor(rayEnd[i]));
            t_next[i] = (rayStart[i] - floorf(rayStart[i])) * dt_delta[i];
        }
    }

    auto argmin = [](glm::vec3 &a) -> int {
        int min = 0;
        for (int i = 1; i < 3; ++i) {
            if (a[i] < a[min]) {
                min = i;
            }
        }
        return min;
    };

    for (; n > 0; --n) {
        Chunk *currentChunk = getChunk(currentBlock.x, currentBlock.z);
        if (currentChunk != nullptr) {
            if (currentChunk->getBlock(currentBlock.x, currentBlock.y, currentBlock.z) != 0) {
                return currentBlock;
            }
        }

        int min = argmin(t_next);
        currentBlock[min] += increment[min];
        t = t_next[min];
        t_next[min] += dt_delta[min];
    }

    return glm::ivec3(-1);
}

void World::removeBlock(int x, int y, int z) {
    Chunk *chunk = getChunk(x, z);
    if (chunk != nullptr) {
        chunk->removeBlock(x, y, z);
    }
}

void World::placeBlock(int x, int y, int z, unsigned type) {
    Chunk *chunk = getChunk(x, z);
    if (chunk != nullptr) {
        chunk->placeBlock(x, y, z, type);
    }
}

Chunk *World::getChunk(int x, int z) {
    auto chunkPosition = std::make_pair<int, int>(int(floorf(x / 16.f)),
                                                  int(floorf(z / 16.f)));
    auto chunkIterator = chunks.find(chunkPosition);
    if (chunkIterator != chunks.end()) {
        return &(*chunkIterator).second;
    }

    return nullptr;
}
