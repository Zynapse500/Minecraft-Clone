//
// Created by Christofer on 19/08/2017.
//

#ifndef MINECRAFT_CLONE_TEXTURESTITCHING_H
#define MINECRAFT_CLONE_TEXTURESTITCHING_H

#include "Texture.h"

/*
 * Takes multiple images and stitches them together
 * into a single texture
 */
Texture stitchTextures(PixelData* pixelDatas, int count);

#endif //MINECRAFT_CLONE_TEXTURESTITCHING_H
