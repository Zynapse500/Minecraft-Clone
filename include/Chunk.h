//
// Created by chris on 14/08/2017.
//

#ifndef MINECRAFT_CLONE_CHUNK_H
#define MINECRAFT_CLONE_CHUNK_H


#include <vector>
#include "Model.h"

class Chunk {

public:

    Chunk() = default;

    // Generates the chunk's terrain based on it's position in the world
    void generate(int x, int z);


    // Renders the chunk
    void draw();


    // Sets the chunk's neighbor in a direction
    void setNeighbor(Chunk* neighbor, int dx, int dz);


    // Removes a block and return it's old type (global coordinates)
    unsigned removeBlock(int x, int y, int z);

private:

    // The model of the chunk
    Model model;

    // Height and size of the chunk (width = depth = size)
    static const unsigned size = 16;
    static const unsigned height = 256;

    // Position of the chunk in the world (y never changes)
    int chunk_x = 0;
    int chunk_z = 0;

    // Block-map of the chunk
    unsigned blockMap[size * size * height];


    // The chunk's neighbors
    Chunk* neighbors[4] = {nullptr};

    // Converts a direction to a neighbor
    Chunk* getNeighbor(int dx, int dz);


    // Returns a reference to the block at location (x, y, z)
    unsigned int * getBlockGlobal(int x, int y, int z);

    // Returns a reference to the block at local location (x, y, z)
    unsigned int * getBlockLocal(int x, int y, int z);


    // Converts global to local coordinates for chunk (y doesn't change)
    void convertToLocal(int *x, int *z);

    // Converts local to global coordinates for chunk (y doesn't change)
    void convertToGlobal(int *x, int *z);

    // Adds a block's face to the building vertices
    void addFace(int x, int y, int z, int dir_x, int dir_y, int dir_z, unsigned block);
    // Vector of vertices and indices used for building the model
    std::vector<Vertex> vertices;

    std::vector<GLuint> indices;


    // Generates the chunk's model
    void generateModel();

    // Returns a height value for coordinates
    int getHeightmapValue(int x, int z);

    void updateNeighboringChunks();
};

#endif //MINECRAFT_CLONE_CHUNK_H
