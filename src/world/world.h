#pragma once
#include "../rendering/render_engine.h"
#include "chunk/chunks_manager.h"
#include "../rendering/camera.h"


class World {

public:
	World();
	~World();

	void update(Camera& camera); 
	void prepareRender(RenderEngine& renderer, Camera& camera); 
	
	Block getBlock(glm::vec3 pos);

private: 
	ChunksManager chunksManager; 
	
};