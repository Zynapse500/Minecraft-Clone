//
// Created by chris on 14/08/2017.
//

#include <iostream>
#include "Chunk.h"

void Chunk::generate(int _x, int _z) {
    chunk_x = _x;
    chunk_z = _z;

    // Generate block-map
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < size; ++z) {
                if (rand() % 100 < 20)
                    *getBlock(x, y, z) = 1;
                else
                    *getBlock(x, y, z) = 0;
            }
        }
    }


    // Generate model
    /* METHOD:
     * For each block, add each face if visible
     */
    glm::ivec3 directions[] = {
            glm::ivec3(1, 0, 0), glm::ivec3(-1, 0, 0),
            glm::ivec3(0, 1, 0), glm::ivec3(0, -1, 0),
            glm::ivec3(0, 0, 1), glm::ivec3(0, 0, -1),
    };

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < size; ++z) {
                unsigned* currentBlock = getBlock(x, y, z);

                if (*currentBlock != 0) {
                    // For every direction check adjacent blocks and add face
                    for (auto& dir : directions) {
                        auto *adjacentBlock = getBlock(x + dir.x,
                                                       y + dir.y,
                                                       z + dir.z);

                        if(adjacentBlock == nullptr || *adjacentBlock == 0)
                            addFace(x, y, z, dir.x, dir.y, dir.z, *currentBlock);
                    }
                }
            }
        }
    }


    model.setVertices(this->vertices.data(), this->vertices.size());
    model.setIndices(this->indices.data(), this->indices.size());

    this->vertices.clear();
    this->indices.clear();
}

unsigned int *Chunk::getBlock(int x, int y, int z) {
    // Convert x and z to local coordinates
    convertToLocal(&x, &z);

    auto isInRage = [](int a, int min, int max) {
        return min <= a && a < max;
    };

    if (!isInRage(x, 0, size))
        return nullptr;
    if (!isInRage(y, 0, height))
        return nullptr;
    if (!isInRage(z, 0, size))
        return nullptr;

    int layer = y * this->size * this->size;
    int row = z * this->size;

    return &(blockMap[x + row + layer]);
}

void Chunk::convertToLocal(int *x, int *z) {
    *x -= this->chunk_x;
    *z -= this->chunk_z;
}

void Chunk::draw() {
    model.draw();
}

void Chunk::addFace(int x, int y, int z, int dir_x, int dir_y, int dir_z, unsigned block) {
    GLuint vertexCount = this->vertices.size();
    GLuint indices[] = {
            vertexCount + 0,
            vertexCount + 1,
            vertexCount + 2,
            vertexCount + 2,
            vertexCount + 3,
            vertexCount + 0
    };

    if (dir_x == 1) {
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1));
    } else if (dir_x == -1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(1, 1));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1));
    } else if (dir_z == 1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1));
    } else if (dir_z == -1) {
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(1, 1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1));
    } else if (dir_y == 1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1));
    } else if (dir_y == -1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(1, 1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 1));
    }


    for (auto& index : indices) {
        this->indices.push_back(index);
    }
}
