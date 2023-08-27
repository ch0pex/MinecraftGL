#pragma once

#include <vector>
#include <thread>
#include <mutex>

#include "world/generators/basic_gen.h"
#include "math/vector_xz.h"
#include "chunk.h"
#include "block.h"

class World;

class ChunksManager {
public:
  explicit ChunksManager(World &world);
  ~ChunksManager();
  void LoadChunks();

  void UpdateChunks(glm::vec3 player_pos);
  std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& GetChunks();
  Block GetBlock(glm::vec3 position);

private:
  std::shared_ptr<Chunk> GetChunk(glm::vec2 xzpos);
  VectorXZ WorldPosToChunkPos(glm::vec3 )
  void BuildChunksMesh();

  World *world_;
  //BasicGen generator_;
  std::unordered_map<VectorXZ, std::shared_ptr<Chunk>> chunks_;
  std::vector<std::thread> chunk_loaders_;
  std::mutex mutex_;

};