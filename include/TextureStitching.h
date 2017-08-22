//
// Created by Christofer on 19/08/2017.
//

#ifndef MINECRAFT_CLONE_TEXTURESTITCHING_H
#define MINECRAFT_CLONE_TEXTURESTITCHING_H

#include "Texture.h"
#include "TextureRegion.h"

/*
 * Takes multiple images and stitches them together
 * into a single texture
 *
 * Adds some padding on the sides of each texture to
 * reduce bleeding
 *
 * Saves each texture's location int the texture
 * in it's respective texture region
 */
Texture stitchTextures(PixelData *pixelDatas, TextureRegion *textureRegions, int count);

#endif //MINECRAFT_CLONE_TEXTURESTITCHING_H
