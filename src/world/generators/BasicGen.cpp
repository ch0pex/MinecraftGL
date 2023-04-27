#include "BasicGen.h"

void BasicGen::genChunk(Chunk& chunk) 
{
	int x;
	int y;
	int z;

	for (u32 i = 0; i < CHUNK_VOLUME; i++)
	{
		x = (i % CHUNK_SIZE);
		y = i / (CHUNK_SIZE * CHUNK_SIZE);
		z = (i / CHUNK_SIZE) % CHUNK_SIZE;
		
		chunk.getChunklet(y)->setBlock( y < 256 ? Block::STONE: Block::AIR); 
		
	}

}
