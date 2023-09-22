#include "basic_gen.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

void BasicGen::FlatGen(Chunk &chunk) {
  int x = 0;
  int y = 0;
  int z = 0;
  Block block;

  for (u32 i = 0; i < kChunkVolume; i++) {
    x = i % kChunkSize;
    y = i / (kChunkSize * kChunkSize);
    z = i / kChunkSize % kChunkSize;
    if(y < 70)
     chunk.GetChunklet(y)->SetBlock(Block::kStone);
    else if (y >= 70 && y <= 90)
      chunk.GetChunklet(y)->SetBlock(Block::kWater);
    else
      chunk.GetChunklet(y)->SetBlock(Block::kAir);
  }
}

void BasicGen::GenChunk(ChunksManager &chunks_manager, u32 chunk_index) {
  int x;
  int y;
  int z;
  Block block;
  u32 chunk_blocks_index = chunk_index * 65536;

  for (u32 i = 0; i < kChunkVolume; i++) {
    x = round(i % kChunkSize);
    y = round(i / (kChunkSize * kChunkSize));
    z = round(i / kChunkSize % kChunkSize);


    x = x +  chunks_manager.chunks_position_[chunk_index] * kChunkSize;
    x = round((cos((x / 12.0)) * 8.0) + 60);

    z = z + chunks_manager.chunks_position_[chunk_index + 1] * kChunkSize;
    z = round(cos((z / 12.0)) * 12.0 + 60);


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
    chunks_manager.blocks_[chunk_blocks_index + i] = block;
  }
}

