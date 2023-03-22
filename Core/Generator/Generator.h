#pragma once

#include "../../Common/CommonHeaders.h"
#include "../Block/Block.h"
#include "../../glm/glm/glm.hpp"


class Generator
{
public: 
	static std::vector<Block>* genChunk(glm::vec2 posXY); 
};

