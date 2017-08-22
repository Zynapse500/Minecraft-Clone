//
// Created by chris on 22/08/2017.
//

#include "Grass.h"

Grass::Grass() : Block(true, true) {}


void Grass::mine(glm::ivec3 position) const {
    std::cout << "Mined: Grass" << std::endl;
}

std::vector<PixelData> Grass::loadTextures() const {
    std::vector<PixelData> pixelData(1);

    PixelData& data = pixelData[0];
    lodepng_decode32_file(&data.pixels, &data.width, &data.height, "resources/textures/grass.png");

    return pixelData;
}
