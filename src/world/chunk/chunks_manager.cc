#include "chunks_manager.h"
#include "world/world.h"
#include "config/config.h"


ChunksManager::ChunksManager(World &world) :
    world_(&world)
{
}

ChunksManager::~ChunksManager() {
}

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
    if(!chunk->IsBuilt())
      chunk->BuildMesh();
  }
}

void ChunksManager::UpdateBufferedChunks(const glm::vec3 &player_pos) {
  const VectorXZ player_chunk_pos = WorldPosToChunkPos(player_pos);
  f32 distance;
  for (auto& [chunk_pos, chunk] : chunks_) {
    distance = DistanceFromChunkToPlayer(chunk_pos, player_chunk_pos);
    if (distance <= kGameConfig.render_distance && chunk->IsBuilt() && !chunk->IsBuffered())
      chunk->BufferChunklets();
    else if (distance > kGameConfig.render_distance && distance <= kGameConfig.chunk_distance && chunk->IsBuffered())
      chunk->UnBufferChunklets();
  }
}

const std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& ChunksManager::GetChunks() {
  return chunks_;
}

void ChunksManager::AddChunk(VectorXZ pos) {
  chunks_[pos] = std::make_shared<Chunk>(*world_, glm::vec2(pos.x, pos.z));
}

Block ChunksManager::GetBlock(glm::vec3 position) const {
  std::shared_ptr<Chunk> chunk = GetChunk(WorldPosToChunkPos(position));
  if (chunk == nullptr)
    return Block::kDirt; //when chunkupdating done change this to kGround
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

  return sqrt(pow(x,2) + pow(z, 2));
}
void ChunksManager::RemoveChunk(VectorXZ pos) {
  chunks_[pos]->UnBufferChunklets();
  chunks_.erase(pos);
}
