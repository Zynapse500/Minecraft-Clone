//
// Created by chris on 22/08/2017.
//

#include "Air.h"

Air::Air(): Block(false, false) {

}

std::vector<PixelData> Air::loadTextures() const {
    return {};
}

void Air::mine(glm::ivec3 position) const {
    // Can't mine air
}

std::tuple<std::vector<Vertex>, std::vector<GLuint>> Air::appendFaces(const Block **neighbors, glm::ivec3 position) const {
    return std::make_tuple(std::move(std::vector<Vertex>()), std::move(std::vector<GLuint>()));
}
