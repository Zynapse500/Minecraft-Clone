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

    PixelData();

    PixelData(const char* path);

    // "pastes" other data's pixels into these at (x, y)
    void blit(const PixelData &data, GLuint destX, GLuint destY);

    // "pastes" other data's pixels into these at (x, y)
    // Adds a 1-pixel border around the blitted image
    // The total pasted width and height is effectively increased by (2 * padding) pixels
    void blitWithPadding(PixelData& data, unsigned int x, unsigned int y, unsigned int padding);

    // Loads a png image from disk
    void load(const char* path);
};


/*
 * Wrapper around GL texture
 */
class Texture {
public:

    Texture();

    // Creates an empty texture with width and height
    Texture(GLuint width, GLuint height);

    // Creates a texture with pixels
    Texture(unsigned char *pixels, GLuint width, GLuint height);
    Texture(PixelData& data);



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
    GLuint getWidth() const { return width; }
    GLuint getHeight() const { return height; }
    glm::ivec2 getSize() const { return glm::ivec2(width, height); }


    // Determines which texture was created first
    bool operator<(const Texture &other) const;


private:

    // Handle to OpenGL texture
    GLuint h_texture;

    GLuint width, height;

};


#endif //MINECRAFT_CLONE_TEXTURE_H
