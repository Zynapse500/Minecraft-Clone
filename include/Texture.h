//
// Created by chris on 11/08/2017.
//

#ifndef MINECRAFT_CLONE_TEXTURE_H
#define MINECRAFT_CLONE_TEXTURE_H

#include <GL/glew.h>


/*
 * Stores the data required for a texture
 */
struct PixelData {
    unsigned char* pixels;
    int width;
    int height;
};



/*
 * Wrapper around GL texture
 */
class Texture {
public:

    // Creates a texture with width and height
    Texture();

    // Sets the pixels of the texture
    void setPixelData(unsigned char *pixels, int width, int height);
    void setPixelData(const PixelData &data);

    // Binds/unbinds this texture
    void bind();
    void unbind();

    // Sets the min and mag mode of the texture
    void setMinMagFilter(int min, int mag);

    // Sets the wrapping mode of the texture
    void setWrapMode(int s, int t);

private:

    // Handle to OpenGL texture
    GLuint h_texture;

};


#endif //MINECRAFT_CLONE_TEXTURE_H
