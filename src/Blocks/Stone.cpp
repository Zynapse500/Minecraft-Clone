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
    std::vector<PixelData> pixelData = {
            "resources/textures/stone.png"
    };

    return pixelData;
}
