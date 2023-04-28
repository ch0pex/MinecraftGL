#pragma once
#include "../generators/BasicGen.h"
#include "chunk.h"
#include <vector>
#include <thread>
#include <mutex>
#include "block.h"

class World; 

class ChunksManager {

private: 
	World *world; 
	BasicGen generator; 
	
	std::vector<Chunk> chunks;
	std::thread chunkLoader; 
	std::vector<std::thread> sectorLoaders; 
	std::mutex mutex; 

	void loadSection(size_t start, size_t end);
	void loadChunks(); 

	Chunk* getChunk(glm::vec2 xzpos);
	void buildChunksMesh(); 
public:

	ChunksManager(World &_world);
	~ChunksManager(); 


	void updateChunks(glm::vec3 playerPos);
	std::vector<Chunk>& getChunks();
	Block getBlock(glm::vec3 position); 
};