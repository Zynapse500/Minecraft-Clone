//
// Created by chris on 11/08/2017.
//

#include "Texture.h"

Texture::Texture() {
    glGenTextures(1, &this->h_texture);
}

void Texture::setPixelData(unsigned char *pixels, int width, int height) {
    glBindTexture(GL_TEXTURE_2D, this->h_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, false, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    setMinMagFilter(GL_NEAREST, GL_NEAREST);

    glBindTexture(GL_TEXTURE_2D, this->h_texture);
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

void Texture::setPixelData(const PixelData &data) {
    setPixelData(data.pixels, data.width, data.height);
}
