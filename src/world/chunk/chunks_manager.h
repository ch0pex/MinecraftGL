#pragma once
#include "../generators/basic_gen.h"
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
	std::vector<std::thread> chunkLoaders; 
	std::mutex mutex; 

	Chunk* getChunk(glm::vec2 xzpos);
	void buildChunksMesh(); 
public:

	ChunksManager(World &_world);
	~ChunksManager(); 
	void loadChunks(); 

	void updateChunks(glm::vec3 playerPos);
	std::vector<Chunk>& getChunks();
	Block getBlock(glm::vec3 position); 
};