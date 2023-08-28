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

  void UpdateChunks(const glm::vec3& player_pos);
  std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& GetChunks();
  Block GetBlock(glm::vec3 position) const;

private:
  std::shared_ptr<Chunk> GetChunk(VectorXZ chunk_pos) const;
  VectorXZ WorldPosToChunkPos(const glm::vec3& world_pos) const;
  bool ChunkInRange(const VectorXZ &player_chunk_pos, const VectorXZ &chunk_pos);
  void BuildChunksMesh();

  World *world_;
  //BasicGen generator_;
  std::unordered_map<VectorXZ, std::shared_ptr<Chunk>> chunks_;
  std::vector<std::thread> chunks_loaders_;
  std::mutex mutex_;

};