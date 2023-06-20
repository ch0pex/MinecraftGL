#pragma once

#include "../../common/public/common_headers.h"


enum class Block : u8 {
    kAir = 0u,
    kStone
};

enum class BlockFace : u8 {
    kFront = 0u,
    kBack,
    kRight,
    kLeft,
    kTop,
    kBottom
};