#pragma once

#include <vector>
#include <thread>
#include <mutex>

#include "world/generators/basic_gen.h"
#include "chunk.h"
#include "block.h"

class World;

class ChunksManager {

private:
  World *world_;
  BasicGen generator_;

  std::vector<Chunk> chunks_;
  std::vector<std::thread> chunk_loaders_;
  std::mutex mutex_;

  Chunk *GetChunk(glm::vec2 xzpos);
  void BuildChunksMesh();
public:
  explicit ChunksManager(World &world);
  ~ChunksManager();
  void LoadChunks();

  void UpdateChunks(glm::vec3 player_pos);
  std::vector<Chunk> &GetChunks();
  Block GetBlock(glm::vec3 position);
};