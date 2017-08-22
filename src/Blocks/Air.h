//
// Created by chris on 22/08/2017.
//

#ifndef MINECRAFT_CLONE_AIR_H
#define MINECRAFT_CLONE_AIR_H


#include <Block.h>

class Air: public Block {
public:
    Air();

    std::vector<PixelData> loadTextures() const override;

    void mine(glm::ivec3 position) const override;

    std::tuple<std::vector<Vertex>, std::vector<GLuint>> appendFaces(const Block **neighbors, glm::ivec3 position) const
            override;
};


#endif //MINECRAFT_CLONE_AIR_H
