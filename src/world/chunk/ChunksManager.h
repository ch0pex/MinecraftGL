#pragma once
#include "../generators/BasicGen.h"
#include "chunk.h"
#include <vector>



class ChunksManager {

private: 
	BasicGen generator; 
	std::vector<Chunk> chunks;

public:

	ChunksManager();
	~ChunksManager(); 
	//Chunk getChunk(glm::vec2 xypos);
	void updateChunks(glm::vec3 playerPos);
	std::vector<Chunk>& getChunks();

};