//
// Created by chris on 22/08/2017.
//

#include "Dirt.h"

Dirt::Dirt(): Block(true, true) {

}

std::vector<PixelData> Dirt::loadTextures() const {
    std::vector<PixelData> pixelData(1);

    PixelData& data = pixelData[0];
    lodepng_decode32_file(&data.pixels, &data.width, &data.height, "resources/textures/dirt.png");

    return pixelData;
}

void Dirt::mine(glm::ivec3 position) const {
    std::cout << "Mined: Dirt" << std::endl;
}
