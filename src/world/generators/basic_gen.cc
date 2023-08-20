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


    if (y < x && y < z) {
      if (y + 1 == x || y + 1 == z)
        block = Block::kGrass;
      else if (y + 5 >= x || y + 5 >= z)
        block = Block::kDirt;
      else
        block = Block::kStone;
    } else block = Block::kAir;

    if (block == Block::kAir && y < 55)
      block = Block::kWater;

    chunk.GetChunklet(y)->SetBlock(block);
  }
}

