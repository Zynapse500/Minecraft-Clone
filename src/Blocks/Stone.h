//
// Created by chris on 22/08/2017.
//

#ifndef MINECRAFT_CLONE_STONE_H
#define MINECRAFT_CLONE_STONE_H

#include <iostream>

#include <Block.h>

class Stone: public Block {
public:

    Stone();

    std::vector<PixelData> loadTextures() const override;

    void mine(glm::ivec3 position) const override;
};


#endif //MINECRAFT_CLONE_STONE_H
