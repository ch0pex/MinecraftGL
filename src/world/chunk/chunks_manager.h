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

  void UpdateBufferedChunks(const glm::vec3& player_pos);
  void BuildChunksMesh();
  Block GetBlock(glm::vec3 position) const;
  VectorXZ WorldPosToChunkPos(const glm::vec3& world_pos) const;
  const std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& GetChunks();
  void AddChunk(VectorXZ pos);
  void RemoveChunk(VectorXZ pos);
  f32 DistanceFromChunkToPlayer(const VectorXZ& chunk_pos, const VectorXZ& player_chunk_pos) const;

private:
  std::shared_ptr<Chunk> GetChunk(VectorXZ chunk_pos) const;

  std::unordered_map<VectorXZ, std::shared_ptr<Chunk>> chunks_;
  World *world_;
};