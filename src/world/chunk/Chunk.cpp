#include "Chunk.h"

Chunk::Chunk(glm::vec2 _position, std::vector<Block>* blocks) 
{
	
}

Chunk::~Chunk()
{

}

bool Chunk::isBuffered()
{
	return buffered;
}


void Chunk::drawChunklets(RenderEngine& renderer)
{

}