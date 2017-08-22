//
// Created by chris on 11/08/2017.
//

#include <IMG/lodepng.h>
#include <stdexcept>
#include "Texture.h"

void PixelData::blit(const PixelData &data, GLuint destX, GLuint destY) {
    for (int y = 0; y < data.height; ++y) {
        for (int x = 0; x < data.width; ++x) {
            int startDestinationIndex = ((destX + x) + (destY + y) * this->width) * 4;
            int startSourceIndex = (x + y * data.width) * 4;
            for (int i = 0; i < 4; ++i) {
                this->pixels[startDestinationIndex + i] = data.pixels[startSourceIndex + i];
            }
        }
    }
}

void PixelData::blitWithPadding(PixelData& data, unsigned int destX, unsigned int destY, unsigned int padding) {

    auto copyInto = [this, &data](int src_x, int src_y, int dest_x, int dest_y) {
        int startDestinationIndex = ((dest_x) + (dest_y) * this->width) * 4;
        int startSourceIndex = (src_x + src_y * data.width) * 4;
        for (int i = 0; i < 4; ++i) {
            this->pixels[startDestinationIndex + i] = data.pixels[startSourceIndex + i];
        }
    };

    for (int y = 0; y < data.height; ++y) {
        for (int x = 0; x < data.width; ++x) {
            copyInto(x, y, destX + x + padding, destY + y + padding);
        }
    }
    
    /*
     * Add padding
     */
    // Horizontal strips
    for (int x = 0; x < data.width; ++x) {
        for (int y = 0; y < padding; ++y) {
            copyInto(x, 0, destX + x + padding, destY + y);
            copyInto(x, data.height - 1, destX + x + padding, destY + data.height + padding + y);
        }
    }
    // Vertical strips
    for (int y = 0; y < data.height; ++y) {
        for (int x = 0; x < padding; ++x) {
            copyInto(0, y, destX + x, destY + y + padding);
            copyInto(data.width - 1, y, destX + data.height + padding + x, destY + y + padding);
        }
    }


    for (int x = 0; x < padding; ++x) {
        for (int y = 0; y < padding; ++y) {
            copyInto(0, 0, destX + x, destY + y);
            copyInto(0, data.height - 1, destX + x, destY + data.height + padding + y);
            copyInto(data.width - 1, 0, destX + data.width + padding + x, destY + y);
            copyInto(data.width - 1, data.height - 1, destX + data.width + padding + x, destY + data.height + padding + y);
        }
    }

    // Corners
}

void PixelData::load(const char *path) {
    unsigned error = lodepng_decode32_file(&pixels, &width, &height, path);
    if(error != 0) {
        throw std::runtime_error("Failed to load image: " + std::string(path));
    }
}

PixelData::PixelData(const char * path) {
    load(path);
}

PixelData::PixelData() {
}


Texture::Texture() {
    glGenTextures(1, &this->h_texture);
}

Texture::Texture(GLuint width, GLuint height): Texture(nullptr, width, height) {
}

Texture::Texture(unsigned char *pixels, GLuint width, GLuint height) : Texture() {
    setPixelData(pixels, width, height);
}

Texture::Texture(PixelData& data): Texture() {
    setPixelData(data);
}

void Texture::setPixelData(unsigned char *pixels, GLuint width, GLuint height) {
    this->width = width, this->height = height;

    glBindTexture(GL_TEXTURE_2D, this->h_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    setMinMagFilter(GL_NEAREST, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, this->h_texture);
}

void Texture::setPixelData(const PixelData &data) {
    setPixelData(data.pixels, data.width, data.height);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, this->h_texture);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::setMinMagFilter(int min, int mag) {
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag);
}

void Texture::setWrapMode(int s, int t) {
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t);
}

bool Texture::operator<(const Texture &other) const {
    return this->h_texture < other.h_texture;
}
