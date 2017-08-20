//
// Created by Christofer on 19/08/2017.
//

#include <algorithm>
#include <vector>
#include "TextureStitching.h"

Texture stitchTextures(PixelData *pixelDatas, TextureRegion *textureRegions, int count) {

    // Data for one of the complete texture's sub-images
    struct SubTexture {
        PixelData &data;
        TextureRegion &region;

        SubTexture(PixelData &_data, TextureRegion &_region) : data(_data), region(_region) {
        }
    };

    // The complete image
    PixelData completeData;

    // The final texture
    Texture& texture = *(new Texture);

    // All sub-textures
    std::vector<SubTexture> subTextures;
    for (int i = 0; i < count; ++i) {
        subTextures.emplace_back(pixelDatas[i], textureRegions[i]);
    }

    // Determine the minimum rectangle to fit every individual texture
    GLuint maxWidth = 0, maxHeight = 0;
    for (auto &subTexture : subTextures) {
        maxHeight = std::max(subTexture.data.height, maxHeight);
        maxWidth = std::max(subTexture.data.width, maxWidth);
    }

    // Determine how many tiles to allocate
    auto horizontalTiles = GLuint(ceilf(sqrtf(count)));
    auto verticalTiles = GLuint(ceilf(float(count) / horizontalTiles));

    // Determine the actual size of the final texture and allocate the bytes
    completeData.width = horizontalTiles * maxWidth;
    completeData.height = verticalTiles * maxHeight;

    completeData.pixels = new unsigned char[completeData.width * completeData.height * 4];

    // Blit all the sub-textures into the complete one
    int x = 0;
    int y = 0;
    for (auto &subTexture : subTextures) {
        unsigned int blit_x = x * maxWidth, blit_y = y * maxHeight;
        completeData.blit(subTexture.data, blit_x, blit_y);

        subTexture.region.texture = &texture;
        subTexture.region.offset = glm::vec2(float(blit_x) / completeData.width, float(blit_y) / completeData.height);
        subTexture.region.size = glm::vec2(float(subTexture.data.width) / completeData.width,
                                           float(subTexture.data.height) / completeData.height);

        x++;
        if (x == horizontalTiles) {
            y++, x = 0;
        }
    }

    texture.setPixelData(completeData);

    return texture;
}
