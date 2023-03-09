#pragma once
#include <vector>
#include "ChunkRenderer.h"
#include "Chunk.h"
#include "../Block/Block.h"

class ChunksManager
{
private: 
	std::vector<Chunk*> chunks; 

public: 
	Chunk getChunk(glm::vec2 xypos); 
	Block getBlock(glm::vec3 position); 

};

