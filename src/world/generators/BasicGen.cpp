#include "BasicGen.h"

std::vector<Block>* BasicGen::genChunk(glm::vec2 posXY)
{
	std::vector<Block>* blocks = new std::vector<Block>();

	for (u32 i = 0; i < CHUNK_VOLUME; i++)
	{
		blocks->push_back( i > 24576 ? Block::AIR : Block::STONE); 
	}
	return blocks; 
}
