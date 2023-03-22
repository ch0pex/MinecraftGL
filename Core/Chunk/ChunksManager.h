#pragma once

#include "../Generator/Generator.h"
#include "../Block/Block.h"
#include <unordered_map>
#include <thread>
#include <mutex>
#include "Chunk.h"

class ChunksManager
{
private: 
	Generator generator; 
	std::vector<Chunk> chunks;
	std::mutex mapLock; 
public: 
	ChunksManager();  
	Chunk getChunk(glm::vec2 xypos);
	void updateChunks(glm::vec3 playerPos);
	std::vector<Chunk>& getChunks();

};

