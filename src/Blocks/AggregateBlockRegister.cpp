//
// Created by chris on 22/08/2017.
//

#include "AggregateBlockRegister.h"

namespace BlockID {
    unsigned Air;
    unsigned Grass;
    unsigned Stone;
    unsigned Dirt;
}

void registerAllBlocks() {
    BlockID::Air = BlockManager::registerBlock<Air>();
    BlockID::Grass = BlockManager::registerBlock<Grass>();
    BlockID::Stone = BlockManager::registerBlock<Stone>();
    BlockID::Dirt = BlockManager::registerBlock<Dirt>();
}