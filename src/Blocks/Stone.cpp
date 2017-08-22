//
// Created by chris on 22/08/2017.
//

#include "Stone.h"

void Stone::mine(glm::ivec3 position) const {
    std::cout << "Mined: Stone" << std::endl;
}

Stone::Stone(): Block(true, true) {

}

std::vector<PixelData> Stone::loadTextures() const {
    std::vector<PixelData> pixelData(1);

    PixelData& data = pixelData[0];
    lodepng_decode32_file(&data.pixels, &data.width, &data.height, "resources/textures/stone.png");

    return pixelData;
}
