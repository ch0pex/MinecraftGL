#pragma once
#include "../../rendering/render_engine.h"
#include "chunklet.h"
#include "../../common/public/common_headers.h"


class World; 


class Chunk {
public:
	Chunk(World& _world, glm::vec2 _position);
	~Chunk();
	
	bool isBuffered();
	bool isBuilded();
	
	void buildMesh();
	void bufferChunklets();
	void drawChunklets(RenderEngine& renderer, Camera& camera);
	
	Block getBlock(glm::vec3 position);
	Chunklet* getChunklet(u8 Ypos);
	glm::vec2 getPosition();

private:
	World* world; 
	glm::vec2 position; 
	std::vector<Chunklet*> chunklets;
	bool buffered, builded;
};