#pragma once

#include <vector>
#include <thread>
#include <mutex>

#include "world/generators/basic_gen.h"
#include "math/vector_xz.h"
#include "chunk.h"
#include "block.h"

class World;
using ChunkMap = std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>;

class ChunksManager {
public:
  explicit ChunksManager(World &world);
  ~ChunksManager();

  void UpdateBufferedChunks(const glm::vec3& player_pos);
  void BuildChunksMesh();
  Block GetBlock(const glm::vec3& position);
  VectorXZ WorldPosToChunkPos(const glm::vec3& world_pos) const;
  const ChunkMap& GetChunks();
  std::shared_ptr<Chunk>& AddChunk(const VectorXZ& pos);
  ChunkMap::const_iterator RemoveChunk(ChunkMap::const_iterator itr);
  f32 DistanceFromChunkToPlayer(const VectorXZ& chunk_pos, const VectorXZ& player_chunk_pos) const;

private:
  std::shared_ptr<Chunk> GetChunk(VectorXZ chunk_pos) const;

  std::mutex mutex_;
  ChunkMap chunks_;
  World *world_;
};