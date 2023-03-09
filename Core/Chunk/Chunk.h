/*16x256x16*/
#pragma once

#include "../../ThirdParty/glm/glm/glm.hpp"
#include "Chunklet.h"
#include "ChunkRenderer.h"

class Chunk
{
private: 
	glm::vec3 position; 
	Chunklet* chunklets[16];
	bool modified; 
	
public: 
	Chunk(); 
	~Chunk(); 
	void drawChunks(); 
	
};

