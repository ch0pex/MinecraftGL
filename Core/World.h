#pragma once
#include "Chunk/ChunksManager.h"
#include <cstdint>
#include <thread>
#include <mutex>

class World
{
private: 
	const uint8_t chunksDistance; 
	ChunksManager* chunksManager; 

	std::thread loadThreads[16];
	std::mutex mutex;
	void updateChunks(); 
	void loadChunks(); 

public:
	World(); 
	void update(); 
};

