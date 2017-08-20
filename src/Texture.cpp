//
// Created by chris on 11/08/2017.
//

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


Texture::Texture() {
    glGenTextures(1, &this->h_texture);
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
