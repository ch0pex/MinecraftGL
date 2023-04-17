#pragma once
#include "../generators/BasicGen.h"
#include "chunk.h"
#include <vector>
#include "block.h"


class World; 

class ChunksManager {

private: 
	World *world; 
	BasicGen generator; 
	std::vector<Chunk> chunks;
	Chunk* getChunk(glm::vec2 xzpos);

public:

	ChunksManager(World &_world);
	~ChunksManager(); 
	void loadChunks(); 
	void updateChunks(glm::vec3 playerPos);
	std::vector<Chunk>& getChunks();
	Block getBlock(glm::vec3 position); 
};