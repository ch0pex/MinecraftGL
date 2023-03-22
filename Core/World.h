#pragma once
#include "../Common/CommonHeaders.h"
#include "Chunk/ChunksManager.h"
#include "../Rendering/Camera.h"
#include <cstdint>
#include <thread>
#include <mutex>

class World
{
private: 
	const u8 chunksDistance; 
	ChunksManager* chunksManager; 
	Camera& camera; 




public:
	World(Camera &camera); 
	~World(); 
	void update(); 
	void prepareRender(RenderEngine &renderer, Camera &camera); 
};

