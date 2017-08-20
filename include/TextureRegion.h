//
// Created by Christofer on 19/08/2017.
//

#ifndef MINECRAFT_CLONE_TEXTUREREGION_H
#define MINECRAFT_CLONE_TEXTUREREGION_H

#include <Batch/glm.h>

#include "Texture.h"

/*
 * Represents a region withing another texture
 */
struct TextureRegion {
    glm::vec2 offset;
    glm::vec2 size;

    Texture* texture;
};


#endif //MINECRAFT_CLONE_TEXTUREREGION_H
