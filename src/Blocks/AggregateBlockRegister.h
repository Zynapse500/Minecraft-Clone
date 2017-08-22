//
// Created by chris on 22/08/2017.
//

#ifndef MINECRAFT_CLONE_AGGREGATEBLOCKREGISTER_H
#define MINECRAFT_CLONE_AGGREGATEBLOCKREGISTER_H

#include <Block.h>

#include "Air.h"
#include "Grass.h"
#include "Stone.h"
#include "Dirt.h"



/*
 * ID's for all the blocks
 */
namespace BlockID {
    extern unsigned Air;
    extern unsigned Grass;
    extern unsigned Stone;
    extern unsigned Dirt;
}


/*
 * Registers all blocks
 */
void registerAllBlocks();





#endif //MINECRAFT_CLONE_AGGREGATEBLOCKREGISTER_H
