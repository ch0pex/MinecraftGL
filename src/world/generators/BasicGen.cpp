#include "BasicGen.h"

std::vector<Block>* BasicGen::genChunk(glm::vec2 posXY)
{
	int x;
	int y;
	int z;
	std::vector<Block>* blocks = new std::vector<Block>();
	blocks->reserve(CHUNK_VOLUME); 

	for (u32 i = 0; i < CHUNK_VOLUME; i++)
	{
		x = i % CHUNK_SIZE;
		y = i / (CHUNK_SIZE * CHUNK_SIZE);
		z = (i / CHUNK_SIZE) % CHUNK_SIZE;

		blocks->push_back( y < 60 ? Block::STONE: Block::AIR); 
	}
	return blocks; 
}
