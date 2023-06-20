#include "basic_gen.h"
#include <cmath>
#include <cstdlib>
#include <ctime>


void BasicGen::GenChunk(Chunk &chunk) {
    int x = 0;
    int y = 0;
    int z = 0;
    Block block;

    for (u32 i = 0; i < kChunkVolume; i++) {
        x = i % kChunkSize;
        y = i / (kChunkSize * kChunkSize);
        z = i / kChunkSize % kChunkSize;


        x = x + chunk.GetPosition().x * kChunkSize;
        x = (cos((x / 12.0)) * 8.0) + 60;

        z = z + chunk.GetPosition().y * kChunkSize;
        z = cos((z / 12.0)) * 12.0 + 60;


        if (y < x && y < z) block = Block::kStone;
        else block = Block::kAir;

        chunk.GetChunklet(y)->SetBlock(block);

    }

}

/*
void BasicGen::GenChunk(Chunk& chunk)
{
	int x;
	int y;
	int z;
	float height_;
	Block block; 
	for (u32 i = 0; i < kChunkVolume; i++)
	{
		x = (i % kChunkSize);
		y = i / (kChunkSize * kChunkSize);
		z = (i / kChunkSize) % kChunkSize;
		height_ = x + chunk.GetPosition().x * kChunkSize;
		height_ = (cos((x)/32.0f) * 12.0f)  + 60.0f;

		if (y < height_) block = Block::kStone;
		else block = Block::kAir;

		chunk.GetChunklet(y)->SetBlock(block);
		
	}

}
*/