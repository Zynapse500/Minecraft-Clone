//
// Created by chris on 21/08/2017.
//

#include "Block.h"

void Block::appendFaces(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Block **neighbors,
                        glm::ivec3 position) {
    int x = position.x,
            y = position.y,
            z = position.z;

    int n_textures = textures.size();

    for (int i = 0; i < 6; ++i) {
        Block *neighbor = neighbors[i];

        GLuint vertexStart = vertices.size();

        TextureRegion& region = textures[i % n_textures];
        float u = region.offset.x,
                v = region.offset.y,
                us = region.size.x,
                vs = region.size.y;

        if (!neighbor->opaque) {
            if (i == 0) {
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), glm::vec2(u + us, v + vs), glm::vec3(1, 0, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z + 1), glm::vec2(u + us, v), glm::vec3(1, 0, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z), glm::vec2(u, v), glm::vec3(1, 0, 0));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z), glm::vec2(u, v + vs), glm::vec3(1, 0, 0));
            } else if (i == 1) {
                vertices.emplace_back(glm::vec3(x, y + 1, z), glm::vec2(u + us, v + vs), glm::vec3(-1, 0, 0));
                vertices.emplace_back(glm::vec3(x, y, z), glm::vec2(u + us, v), glm::vec3(-1, 0, 0));
                vertices.emplace_back(glm::vec3(x, y, z + 1), glm::vec2(u, v), glm::vec3(-1, 0, 0));
                vertices.emplace_back(glm::vec3(x, y + 1, z + 1), glm::vec2(u, v + vs), glm::vec3(-1, 0, 0));
            } else if (i == 2) {
                vertices.emplace_back(glm::vec3(x, y + 1, z + 1), glm::vec2(u + us, v + vs), glm::vec3(0, 1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), glm::vec2(u + us, v), glm::vec3(0, 1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z), glm::vec2(u, v), glm::vec3(0, 1, 0));
                vertices.emplace_back(glm::vec3(x, y + 1, z), glm::vec2(u, v + vs), glm::vec3(0, 1, 0));
            } else if (i == 3) {
                vertices.emplace_back(glm::vec3(x, y, z), glm::vec2(u + us, v + vs), glm::vec3(0, -1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z), glm::vec2(u + us, v), glm::vec3(0, -1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z + 1), glm::vec2(u, v), glm::vec3(0, -1, 0));
                vertices.emplace_back(glm::vec3(x, y, z + 1), glm::vec2(u, v + vs), glm::vec3(0, -1, 0));
            } else if (i == 4) {
                vertices.emplace_back(glm::vec3(x, y + 1, z + 1), glm::vec2(u + us, v + vs), glm::vec3(0, 0, 1));
                vertices.emplace_back(glm::vec3(x, y, z + 1), glm::vec2(u + us, v), glm::vec3(0, 0, 1));
                vertices.emplace_back(glm::vec3(x + 1, y, z + 1), glm::vec2(u, v), glm::vec3(0, 0, 1));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1), glm::vec2(u, v + vs), glm::vec3(0, 0, 1));
            } else {
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z), glm::vec2(u + us, v + vs), glm::vec3(0, 0, -1));
                vertices.emplace_back(glm::vec3(x + 1, y, z), glm::vec2(u + us, v), glm::vec3(0, 0, -1));
                vertices.emplace_back(glm::vec3(x, y, z), glm::vec2(u, v), glm::vec3(0, 0, -1));
                vertices.emplace_back(glm::vec3(x, y + 1, z), glm::vec2(u, v + vs), glm::vec3(0, 0, -1));
            }
        }

        indices.push_back(vertexStart + 0);
        indices.push_back(vertexStart + 1);
        indices.push_back(vertexStart + 2);
        indices.push_back(vertexStart + 2);
        indices.push_back(vertexStart + 3);
        indices.push_back(vertexStart + 0);
    }
}
