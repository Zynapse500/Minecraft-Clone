//
// Created by chris on 14/08/2017.
//

#include <iostream>
#include "Chunk.h"

void Chunk::generate(int _x, int _z) {
    chunk_x = _x;
    chunk_z = _z;

    // Generate heightmap
    int heightmap[size][size];
    for (int x = 0; x < size; x++) {
        for (int z = 0; z < size; ++z) {
            heightmap[x][z] = getHeightmapValue(x + _x * size, z + _z * size);
        }
    }

    // Generate block-map
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < height; ++y) {
            for (int z = 0; z < size; ++z) {
                int height = heightmap[x][z];

                if (y <= height)
                    *getBlockLocal(x, y, z) = 1;
                else
                    *getBlockLocal(x, y, z) = 0;
            }
        }
    }


    generateModel();
}

unsigned int *Chunk::getBlockGlobal(int x, int y, int z) {
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

unsigned int *Chunk::getBlockLocal(int x, int y, int z) {
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

    x += this->size * chunk_x;
    z += this->size * chunk_z;

    auto vertexCount = GLuint(this->vertices.size());
    GLuint indices[] = {
            vertexCount + 0,
            vertexCount + 1,
            vertexCount + 2,
            vertexCount + 2,
            vertexCount + 3,
            vertexCount + 0
    };

    if (dir_x == 1) {
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::vec3(1, 0, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), glm::vec3(1, 0, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), glm::vec3(1, 0, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), glm::vec3(1, 0, 0));
    } else if (dir_x == -1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(1, 1), glm::vec3(-1, 0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), glm::vec3(-1, 0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0), glm::vec3(-1, 0, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1), glm::vec3(-1, 0, 0));
    } else if (dir_z == 1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::vec3(0, 0, 1));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(1, 0), glm::vec3(0, 0, 1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0), glm::vec3(0, 0, 1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(0, 1), glm::vec3(0, 0, 1));
    } else if (dir_z == -1) {
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(1, 1), glm::vec3(0, 0, -1));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), glm::vec3(0, 0, -1));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(0, 0), glm::vec3(0, 0, -1));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), glm::vec3(0, 0, -1));
    } else if (dir_y == 1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z + 0.5), glm::vec2(1, 1), glm::vec3(0, 1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z + 0.5), glm::vec2(1, 0), glm::vec3(0, 1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y + 0.5, z - 0.5), glm::vec2(0, 0), glm::vec3(0, 1, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y + 0.5, z - 0.5), glm::vec2(0, 1), glm::vec3(0, 1, 0));
    } else if (dir_y == -1) {
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z - 0.5), glm::vec2(1, 1), glm::vec3(0, -1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z - 0.5), glm::vec2(1, 0), glm::vec3(0, -1, 0));
        this->vertices.emplace_back(glm::vec3(x + 0.5, y - 0.5, z + 0.5), glm::vec2(0, 0), glm::vec3(0, -1, 0));
        this->vertices.emplace_back(glm::vec3(x - 0.5, y - 0.5, z + 0.5), glm::vec2(0, 1), glm::vec3(0, -1, 0));
    }


    for (auto& index : indices) {
        this->indices.push_back(index);
    }
}

void Chunk::generateModel() {
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
                unsigned* currentBlock = getBlockLocal(x, y, z);

                if (*currentBlock != 0) {
                    // For every direction check adjacent blocks and add face
                    for (auto& dir : directions) {
                        auto *adjacentBlock = getBlockLocal(x + dir.x,
                                                            y + dir.y,
                                                            z + dir.z);

                        if(adjacentBlock == nullptr || *adjacentBlock == 0)
                            addFace(x, y, z, dir.x, dir.y, dir.z, *currentBlock);
                    }
                }
            }
        }
    }


    model.setVertices(this->vertices.data(), GLuint(this->vertices.size()));
    model.setIndices(this->indices.data(), GLuint(this->indices.size()));

    this->vertices.clear();
    this->indices.clear();
}

int Chunk::getHeightmapValue(int x, int z) {

    int a = (abs(x) % 64);
    int b = (abs(z) % 64);

    return a + b;
}
