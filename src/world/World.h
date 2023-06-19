#pragma once
#include "../rendering/RenderEngine.h"
#include "chunk/ChunksManager.h"
#include "../rendering/Camera.h"


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