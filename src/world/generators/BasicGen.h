#pragma once
#include "../chunk/block.h"
#include <vector>
#include <glm/glm/glm.hpp>


class BasicGen {
public:
	
	static std::vector<Block>* genChunk(glm::vec2 posXY); 
	
};