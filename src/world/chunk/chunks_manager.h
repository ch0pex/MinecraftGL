#pragma once

#include <vector>
#include <thread>
#include <mutex>

#include "math/vector_xz.h"
#include "block.h"
#include "config/config.h"
#include "rendering/mesh.h"

class World;
using ChunkMap = std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>;

class ChunksManager {
public:
  friend class BasicGen;
  explicit ChunksManager(World &world);
  ~ChunksManager();

  void UpdateBufferedChunks(const glm::vec3& player_pos);
  void BuildChunksMesh();
  Block GetBlock(const glm::vec3& position);
  VectorXZ WorldPosToChunkPos(const glm::vec3& world_pos) const;
  const ChunkMap& GetChunks();
  i32 AddChunk(i32 x, i32 z);
  i32 RemoveChunk(i32 x, i32 z);
  f32 DistanceFromChunkToPlayer(const VectorXZ& chunk_pos, const VectorXZ& player_chunk_pos) const;

private:
  std::shared_ptr<Chunk> GetChunk(VectorXZ chunk_pos) const;
  i32 CreateChunk(u32 index, i32 x, i32 z );
  //ChunkMap chunks_;
  World *world_;

  //Chunks representation in data oriented
  i32 chunks_position_[2048]; //Stride = 2 (chunk_position.x, chunk_position.z) will act as index, nulled with the min value
  std::atomic<bool> render_info_[2048]; //Stride = 2 (buffered_, built_)
  //Chunklets info
  std::vector<Block> blocks_; //Stride = 4096 * 16 = 65536 (cada 65536 bloques tenemos un chunk)
  Mesh meshes_[32768]; //Stride = 2 * 16 = 32 (2 tipos de meshes por chunklet)
  i64 chunklets_position_[49152]; //Stride = 3 * 16 = 48 (world_chunklet_pos.x, world_chunklet_pos.y, world_chunklet_pos.z)
};