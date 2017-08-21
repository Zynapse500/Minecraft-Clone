//
// Created by chris on 21/08/2017.
//

#ifndef MINECRAFT_CLONE_BLOCK_H
#define MINECRAFT_CLONE_BLOCK_H

#include <vector>
#include "TextureRegion.h"
#include "Model.h"

/*
 * Represents a block
 */
class Block {

    // Is the block fully opaque?
    bool opaque;

    // Can the player collide with this block?
    bool solid;


    // Texture regions used for rendering each face
    std::vector<TextureRegion> textures;

public:
    /*
     * Appends this block's vertices and indices to a chunk
     * based on it's surrounding blocks
     *
     * By default it appends the a "regular" block
     *
     * vertices: array of vertices to append to
     * indices: array of indices to append to
     * neighbors: array of Block* in order (x, -x, y, -y, z, -z)
     * position: the position of the block in the world
     */
    virtual void appendFaces(std::vector<Vertex>& vertices, std::vector<GLuint>& indices, Block **neighbors,
                             glm::ivec3 position);


    // What happens when this block is mined?
    virtual void mine(glm::ivec3 position) = 0;
};



#endif //MINECRAFT_CLONE_BLOCK_H
