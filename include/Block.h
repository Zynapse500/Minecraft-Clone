//
// Created by chris on 21/08/2017.
//

#ifndef MINECRAFT_CLONE_BLOCK_H
#define MINECRAFT_CLONE_BLOCK_H

#include <vector>
#include <tuple>

#include "IMG/lodepng.h"

#include "TextureRegion.h"
#include "TextureStitching.h"
#include "Model.h"


class BlockManager;

/*
 * Represents a block
 */
class Block {
    friend class BlockManager;

protected:


public:
    // Texture regions used for rendering each face
    std::vector<TextureRegion> textures;

    // Constructor
    Block(bool opaque, bool solid) :
            opaque(opaque),
            solid(solid) {}

    // Is the block fully opaque?
    const bool opaque;

    // Can the player collide with this block?
    const bool solid;


    /*
     * Appends this block's vertices and indices to a chunk
     * based on it's surrounding blocks
     *
     * Defualts to a "regular" block
     *
     * return: tuple of vertices and indices of this block's mesh
     *
     * neighbors: array of Block* in order (x, -x, y, -y, z, -z)
     * position: the position of the block in the world
     */
    virtual std::tuple<std::vector<Vertex>, std::vector<GLuint>> appendFaces(const Block **neighbors,
                                                                             glm::ivec3 position) const;


    /*
     * Loads all the textures for this block
     * and returns their pixels
     *
     * When registering the block these textures
     * will be placed into the 'textures' member
     * in the same order they were returned
     */
    virtual std::vector<PixelData> loadTextures() const;


    // What happens when this block is mined?
    virtual void mine(glm::ivec3 position) const = 0;
};


class BlockManager {

public:

    /*
     * Adds a instance of 'Block' to the dictionary
     *
     * Return a unique ID for this block
     */
    template<typename T>
    static unsigned registerBlock();


    /*
     * Loads all the textures for the blocks
     */
    static void loadTextures();


    /*
     * Returns a block based on id
     */
    static const Block& getBlock(unsigned id);

    /*
     * Contains the textures for all the registered blocks
     */
    static Texture *blockTextureAtlas;

    static int getBlockCount();

private:

    /*
     * Contains all instances of blocks
     */
    static std::vector<Block *> blockDictionary;


};

template<typename T>
unsigned BlockManager::registerBlock() {
    static_assert(std::is_base_of<Block, T>::value, "T must inherit from 'Block'");

    unsigned id = blockDictionary.size();
    blockDictionary.push_back(new T());

    return id;
}


#endif //MINECRAFT_CLONE_BLOCK_H
