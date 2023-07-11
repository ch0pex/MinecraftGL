#pragma once

#include "../../common/public/common_headers.h"

enum Block {
    kAir = 0u,
    kDirt,
    kGrass,
    kStone,
    kWater,
};

enum class BlockFace : u8 { kFront = 0u,
    kBack,
    kRight,
    kLeft,
    kTop,
    kBottom
};

struct BlockAtlas{
    u8 front;
    u8 back;
    u8 right;
    u8 left;
    u8 top;
    u8 bottom;
};

constexpr BlockAtlas kBlockAtlasIds[5] = {
    {0, 0, 0, 0, 0, 0},  // Air
    {2, 2, 2, 2, 2, 2},  // Dirt
    {1, 1, 1, 1, 0, 2},  // Grass
    {3, 3, 3, 3, 3, 3},  // Stone
    {8, 8, 8, 8, 8, 8}   // Water
};
