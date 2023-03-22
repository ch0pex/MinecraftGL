/*16x256x16*/
#pragma once

#include "../../ThirdParty/glm/glm/glm.hpp"
#include "Chunklet.h"
#include "../Block/Block.h"
#include <vector>

class RenderEngine; 

class Chunk
{
private: 
	glm::vec2 position; 
	std::vector<Chunklet*> chunklets; 
	bool buffered; 

	
public: 
	Chunk(glm::vec2 _position, std::vector<Block>* blocks); 
	~Chunk(); 
	void drawChunklets(RenderEngine &renderer); 
	inline bool isBuffered() { return buffered; }

	
};

