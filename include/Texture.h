//
// Created by chris on 11/08/2017.
//

#ifndef MINECRAFT_CLONE_TEXTURE_H
#define MINECRAFT_CLONE_TEXTURE_H

#include <GL/glew.h>
#include "Batch/glm.h"


/*
 * Stores the data required for a texture
 */
struct PixelData {
    unsigned char *pixels = nullptr;
    unsigned int width = 0;
    unsigned int height = 0;

    // "pastes" pixels into these at (x, y)
    void blit(const PixelData &data, GLuint destX, GLuint destY);
};


/*
 * Wrapper around GL texture
 */
class Texture {
public:

    // Creates a texture with width and height
    Texture();

    // Sets the pixels of the texture
    void setPixelData(unsigned char *pixels, GLuint width, GLuint height);

    void setPixelData(const PixelData &data);

    // Binds/unbinds this texture
    void bind();

    void unbind();

    // Sets the min and mag mode of the texture
    void setMinMagFilter(int min, int mag);

    // Sets the wrapping mode of the texture
    void setWrapMode(int s, int t);

    // Returns the width and the height of the texture
    GLuint getWidth() { return width; }
    GLuint getHeight() { return height; }
    glm::ivec2 getSize() { return glm::ivec2(width, height); }


    // Determines which texture was created first
    bool operator<(const Texture &other) const;


private:

    // Handle to OpenGL texture
    GLuint h_texture;

    GLuint width, height;

};


#endif //MINECRAFT_CLONE_TEXTURE_H
