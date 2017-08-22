//
// Created by chris on 22/08/2017.
//

#ifndef MINECRAFT_CLONE_GRASS_H
#define MINECRAFT_CLONE_GRASS_H

#include <iostream>

#include <Block.h>

class Grass: public Block {
public:

    Grass();

    // Load the textures of this block
    std::vector<PixelData> loadTextures() const override;

    // What happens when this block is mined?
    void mine(glm::ivec3 position) const override;

};


#endif //MINECRAFT_CLONE_GRASS_H
