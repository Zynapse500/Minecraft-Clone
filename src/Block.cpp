//
// Created by chris on 21/08/2017.
//

#include "Block.h"


std::tuple<std::vector<Vertex>, std::vector<GLuint>>
Block::appendFaces(const Block **neighbors, glm::ivec3 position) const {
    static std::vector<Vertex> vertices;
    static std::vector<GLuint> indices;

    vertices.clear();
    indices.clear();

    int x = position.x,
            y = position.y,
            z = position.z;

    int n_textures = textures.size();

    for (int i = 0; i < 6; ++i) {
        const Block *neighbor = neighbors[i];

        GLuint vertexStart = vertices.size();

        const TextureRegion& region = textures[getTextureIndex(BlockSide(i)) % n_textures];
        float u = region.offset.x,
                v = region.offset.y,
                us = region.size.x,
                vs = region.size.y;

        if (neighbor == nullptr || !neighbor->opaque) {
            if (i == 0) {
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1),
                                      glm::vec2(u + us, v), glm::vec3(1, 0, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z + 1),
                                      glm::vec2(u + us, v + vs), glm::vec3(1, 0, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z),
                                      glm::vec2(u, v + vs), glm::vec3(1, 0, 0));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z),
                                      glm::vec2(u, v), glm::vec3(1, 0, 0));
            } else if (i == 1) {
                vertices.emplace_back(glm::vec3(x, y + 1, z),
                                      glm::vec2(u + us, v), glm::vec3(-1, 0, 0));
                vertices.emplace_back(glm::vec3(x, y, z),
                                      glm::vec2(u + us, v + vs), glm::vec3(-1, 0, 0));
                vertices.emplace_back(glm::vec3(x, y, z + 1),
                                      glm::vec2(u, v + vs), glm::vec3(-1, 0, 0));
                vertices.emplace_back(glm::vec3(x, y + 1, z + 1),
                                      glm::vec2(u, v), glm::vec3(-1, 0, 0));
            } else if (i == 2) {
                vertices.emplace_back(glm::vec3(x, y + 1, z + 1),
                                      glm::vec2(u + us, v), glm::vec3(0, 1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1),
                                      glm::vec2(u + us, v + vs), glm::vec3(0, 1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z),
                                      glm::vec2(u, v + vs), glm::vec3(0, 1, 0));
                vertices.emplace_back(glm::vec3(x, y + 1, z),
                                      glm::vec2(u, v), glm::vec3(0, 1, 0));
            } else if (i == 3) {
                vertices.emplace_back(glm::vec3(x, y, z),
                                      glm::vec2(u + us, v), glm::vec3(0, -1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z),
                                      glm::vec2(u + us, v + vs), glm::vec3(0, -1, 0));
                vertices.emplace_back(glm::vec3(x + 1, y, z + 1),
                                      glm::vec2(u, v + vs), glm::vec3(0, -1, 0));
                vertices.emplace_back(glm::vec3(x, y, z + 1),
                                      glm::vec2(u, v), glm::vec3(0, -1, 0));
            } else if (i == 4) {
                vertices.emplace_back(glm::vec3(x, y + 1, z + 1),
                                      glm::vec2(u + us, v), glm::vec3(0, 0, 1));
                vertices.emplace_back(glm::vec3(x, y, z + 1),
                                      glm::vec2(u + us, v + vs), glm::vec3(0, 0, 1));
                vertices.emplace_back(glm::vec3(x + 1, y, z + 1),
                                      glm::vec2(u, v + vs), glm::vec3(0, 0, 1));
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z + 1),
                                      glm::vec2(u, v), glm::vec3(0, 0, 1));
            } else {
                vertices.emplace_back(glm::vec3(x + 1, y + 1, z),
                                      glm::vec2(u + us, v), glm::vec3(0, 0, -1));
                vertices.emplace_back(glm::vec3(x + 1, y, z),
                                      glm::vec2(u + us, v + vs), glm::vec3(0, 0, -1));
                vertices.emplace_back(glm::vec3(x, y, z),
                                      glm::vec2(u, v + vs), glm::vec3(0, 0, -1));
                vertices.emplace_back(glm::vec3(x, y + 1, z),
                                      glm::vec2(u, v), glm::vec3(0, 0, -1));
            }

            indices.push_back(vertexStart + 0);
            indices.push_back(vertexStart + 1);
            indices.push_back(vertexStart + 2);
            indices.push_back(vertexStart + 2);
            indices.push_back(vertexStart + 3);
            indices.push_back(vertexStart + 0);
        }
    }

    return std::make_tuple(std::move(vertices), std::move(indices));
}

std::vector<PixelData> Block::loadTextures() const {

    std::vector<PixelData> pixelData(1);

    pixelData[0].load("resources/textures/nan.png");

    return pixelData;
}

unsigned Block::getTextureIndex(BlockSide side) const {
    return 0;
}


std::vector<Block *> BlockManager::blockDictionary;
Texture *BlockManager::blockTextureAtlas;


void BlockManager::loadTextures() {
    // The combined pixel data of all blocks
    std::vector<PixelData> pixelData;

    // The number of pixel data each block outputted
    std::vector<int> outputCount;


    // Get all the pixel data from the blocks
    for (auto&& block : blockDictionary) {
        std::vector<PixelData> data = std::move(block->loadTextures());

        pixelData.insert(pixelData.end(), data.begin(), data.end());

        outputCount.push_back(data.size());
    }

    // Number of textures
    unsigned totalTextureCount = pixelData.size();

    // Texture regions to pass into blocks
    std::vector<TextureRegion> regions(totalTextureCount);

    // Create a texture atlas
    blockTextureAtlas = new Texture;
    *blockTextureAtlas = stitchTextures(pixelData.data(), regions.data(), totalTextureCount);
    blockTextureAtlas->setMinMagFilter(GL_LINEAR, GL_NEAREST);

    // Assign texture regions of atlas to blocks
    auto regionIterator = regions.begin();
    int blockIndex = 0;
    for (auto&& block : blockDictionary) {
        auto nextIterator = regionIterator + outputCount[blockIndex];

        block->textures.insert(block->textures.end(), regionIterator, nextIterator);

        regionIterator = nextIterator;
        blockIndex++;
    }
}

const Block& BlockManager::getBlock(unsigned id) {
    return *blockDictionary[id];
}

int BlockManager::getBlockCount() {
    return blockDictionary.size();
}
