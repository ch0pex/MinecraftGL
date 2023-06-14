#pragma once
#include "../../rendering/RenderEngine.h"
#include "Chunklet.h"
#include "../../common/public/CommonHeaders.h"


class World; 


class Chunk {

private:
	World* world; 
	glm::vec2 position; 
	std::vector<Chunklet*> chunklets;
	bool buffered, builded;


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
};