#include "BasicGen.h"
#include <cmath>
#include <cstdlib>
#include <ctime>



void BasicGen::genChunk(Chunk& chunk) 
{
	int x = 0;
	int y = 0;
	int z = 0;
	Block block;
	 
	for (u32 i = 0; i < CHUNK_VOLUME; i++)
	{	
		x = (i % CHUNK_SIZE);
		y = i / (CHUNK_SIZE * CHUNK_SIZE);
		z = i / CHUNK_SIZE % CHUNK_SIZE;
		
		
		x = x + chunk.getPosition().x * CHUNK_SIZE;
		x = (cos((x / 12.0)) * 8.0)  + 60 ;

		z = z + chunk.getPosition().y * CHUNK_SIZE;
		z = cos((z/12.0)) * 12.0  + 60 ;


		if (y < x && y < z) block = Block::STONE; 
		else block = Block::AIR; 

		chunk.getChunklet(y)->setBlock(block); 
		
	}

}

/*
void BasicGen::genChunk(Chunk& chunk) 
{
	int x;
	int y;
	int z;
	float height;
	Block block; 
	for (u32 i = 0; i < CHUNK_VOLUME; i++)
	{
		x = (i % CHUNK_SIZE);
		y = i / (CHUNK_SIZE * CHUNK_SIZE);
		z = (i / CHUNK_SIZE) % CHUNK_SIZE;
		height = x + chunk.getPosition().x * CHUNK_SIZE;
		height = (cos((x)/32.0f) * 12.0f)  + 60.0f;

		if (y < height) block = Block::STONE; 
		else block = Block::AIR; 

		chunk.getChunklet(y)->setBlock(block); 
		
	}

}
*/