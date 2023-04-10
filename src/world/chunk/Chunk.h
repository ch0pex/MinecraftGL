#pragma once
#include "../../rendering/RenderEngine.h"
#include "Chunklet.h"


class Chunk {

private:
	bool buffered;

public:

	Chunk(glm::vec2 _position, std::vector<Block>* blocks);
	~Chunk();
	bool isBuffered();
	void drawChunklets(RenderEngine& renderer); 
	
};