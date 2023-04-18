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
	Chunk(World& _world, glm::vec2 _position, std::vector<Block>* _blocks);
	~Chunk();
	bool isBuffered();
	bool isBuilded(); 
	void loadChunklets(); 
	void drawChunklets(RenderEngine& renderer); 
	Block getBlock(glm::vec3 position);
	glm::vec2 getPosition(); 
};