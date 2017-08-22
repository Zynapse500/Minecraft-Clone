//
// Created by chris on 22/08/2017.
//

#include "Grass.h"

Grass::Grass() : Block(true, true) {}


void Grass::mine(glm::ivec3 position) const {
    std::cout << "Mined: Grass" << std::endl;
}

std::vector<PixelData> Grass::loadTextures() const {
    std::vector<PixelData> pixelData(3);

    PixelData& top = pixelData[0];
    lodepng_decode32_file(&top.pixels, &top.width, &top.height, "resources/textures/grass.png");

    PixelData& side = pixelData[1];
    lodepng_decode32_file(&side.pixels, &side.width, &side.height, "resources/textures/grass_side.png");

    PixelData& bottom = pixelData[2];
    lodepng_decode32_file(&bottom.pixels, &bottom.width, &bottom.height, "resources/textures/dirt.png");

    return pixelData;
}

unsigned int Grass::getTextureIndex(BlockSide side) const {
    unsigned texture = 0;

    if(side == BlockSide::TOP)
        texture = 0;
    else if(side == BlockSide::BOTTOM)
        texture = 2;
    else
        texture = 1;

    return texture;
}
