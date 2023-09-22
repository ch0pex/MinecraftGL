#include "chunks_manager.h"

#include <utility>
#include "world/world.h"
#include "config/config.h"
#include "world/generators/basic_gen.h"


ChunksManager::ChunksManager(World &world) :
    world_(&world)
{
  blocks_.reserve(67108864);

  for (size_t i = 0; i < 1024; i++) {
    chunks_position_[i * 2] = INT32_MIN;
    chunks_position_[(i * 2) + 1] = INT32_MIN;
  }


}

ChunksManager::~ChunksManager() = default;


std::shared_ptr<Chunk> ChunksManager::GetChunk(VectorXZ chunk_pos) const{
  if (chunks_.find(chunk_pos) != chunks_.end())
    return chunks_.at(chunk_pos);
  return nullptr;
}


void ChunksManager::BuildChunksMesh() {
  std::cout << chunks_.size() << "\n";
  for (auto& [chunk_pos, chunk] : chunks_) {
    if (!world_->IsActive())
      return;
    if(!chunk->IsBuilt() && DistanceFromChunkToPlayer(chunk_pos, {0,0}) < kGameConfig.chunk_distance)
      chunk->BuildMesh();
  }
}

void ChunksManager::UpdateBufferedChunks(const glm::vec3 &player_pos) {
  const VectorXZ player_chunk_pos = WorldPosToChunkPos(player_pos);
  f32 distance;
  for (auto &[chunk_pos, chunk] : chunks_) {
    distance = DistanceFromChunkToPlayer(chunk_pos, player_chunk_pos);
    if (chunk->IsBuilt() && !chunk->IsBuffered() && distance <= kGameConfig.render_distance)
      chunk->BufferChunklets();
    else if (distance > kGameConfig.render_distance && chunk->IsBuffered())
      chunk->UnBufferChunklets();
  }
}

const std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& ChunksManager::GetChunks() {
  return chunks_;
}

i32 ChunksManager::CreateChunk(u32 index, i32 x, i32 z) {
  u32 chunklets_index = index * 48;
  chunks_position_[index] = x;
  chunks_position_[index + 1] = z;
  render_info_[index] = false;
  render_info_[index + 1] = false;
  for (size_t i = 0; i < kChunkSize * 2; i++)
    meshes_[(index * 32) + i] = Mesh();
  for (i64 y = 0; y < kChunkSize * 3; y += 3){
    chunklets_position_[chunklets_index] =  x;
    chunklets_position_[chunklets_index + 1] = y;
    chunklets_position_[chunklets_index + 2] = z;
  }
  BasicGen::GenChunk(*this, index);
}

i32 ChunksManager::AddChunk(i32 x, i32 z) {
  for (u32 i = 0; i < 1024; i+=2) {
    if (chunks_position_[i] == INT32_MIN)
      CreateChunk(i, x, z);
    else if (chunks_position_[2048 - i - 2] == INT32_MIN)
      CreateChunk(2048 - i - 2, x, z);
  }
}

// removing a chunks is just as simple as putting the min value to the position of that chunk
i32 ChunksManager::RemoveChunk(int x, int z) {
  for (u32 i = 0; i < 1024; i+=2) {
    if (chunks_position_[i] == x && chunks_position_[i + 1] == z) {
      chunks_position_[i] = std::numeric_limits<i32>::min();
      chunks_position_[i + 1] = std::numeric_limits<i32>::min();
    }
    else if (chunks_position_[2048 - i - 2] == x && chunks_position_[2048 - i - 1] == z) {
      chunks_position_[2048 - i - 2] = std::numeric_limits<i32>::min();
      chunks_position_[2048 - i  - 1] = std::numeric_limits<i32>::min();
    }
  }
}

Block ChunksManager::GetBlock(const glm::vec3& position){
  VectorXZ chunk_pos = WorldPosToChunkPos(position);
  std::shared_ptr<Chunk> chunk = GetChunk(chunk_pos);
  if (chunk == nullptr)
    chunk = AddChunk(chunk_pos);
  return chunk->GetBlock(position);
}

VectorXZ ChunksManager::WorldPosToChunkPos(const glm::vec3 &world_pos) const {
  i64 chunkX = world_pos.x >= 0 ? world_pos.x / 16 : (world_pos.x - 15) / 16;
  i64 chunkZ = world_pos.z >= 0 ? world_pos.z / 16 : (world_pos.z - 15) / 16;
  return {chunkX, chunkZ};
}

f32 ChunksManager::DistanceFromChunkToPlayer(const VectorXZ &chunk_pos, const VectorXZ &player_chunk_pos) const {
  f64 x = abs(player_chunk_pos.x - chunk_pos.x);
  f64 z = abs(player_chunk_pos.z - chunk_pos.z);

  return x > z ? x : z;
  //return sqrt(pow(x,2) + pow(z, 2));
}

