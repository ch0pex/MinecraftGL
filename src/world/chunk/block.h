#pragma once

#include "../../common/public/CommonHeaders.h"



enum class Block : u8 {
	AIR = 0u, 
	STONE
};

enum class BlockFace : u8 {
	FRONT = 0u,
	BACK,
	RIGHT,
	LEFT,
	TOP,
	BOTTOM
};