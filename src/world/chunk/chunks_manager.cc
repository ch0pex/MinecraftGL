#include "chunks_manager.h"
#include "world/world.h"
#include "config/config.h"


ChunksManager::ChunksManager(World &world) :
    world_(&world) {
  std::cout << "Chunks Loading... \n";
  chunks_loaders_.emplace_back([&]() { LoadChunks(); });
}

ChunksManager::~ChunksManager() {
  for (auto &thread: chunks_loaders_)
    thread.join();
}

std::shared_ptr<Chunk> ChunksManager::GetChunk(VectorXZ chunk_pos) const{
  if (chunks_.find(chunk_pos) != chunks_.end())
    return chunks_.at(chunk_pos);
  return nullptr;
}

void ChunksManager::LoadChunks() {
  for (i8 x = -kGameConfig.chunk_distance; x < kGameConfig.chunk_distance; x++) {
    for (i8 z = -kGameConfig.chunk_distance; z < kGameConfig.chunk_distance; z++) {
      if (!world_->IsActive())
        return;
      std::unique_lock<std::mutex> lock(mutex_);
      chunks_[{x, z}] = std::make_shared<Chunk>(*world_, glm::vec2(x, z));
    }
  }

  std::cout << "Chunks generated: " << chunks_.size() << "\n";
  BuildChunksMesh();
  std::cout << "Chunks loaded: " << chunks_.size() << "\n";
}

void ChunksManager::BuildChunksMesh() {
  std::cout << chunks_.size() << "\n";
  for (auto& [chunk_pos, chunk] : chunks_) {
    if (!world_->IsActive()) return;
    chunk->BuildMesh();
  }
}

void ChunksManager::UpdateChunks() {
  for (auto& [chunk_pos, chunk] : chunks_) {
    if (chunk->IsBuilt() && !chunk->IsBuffered())
      chunk->BufferChunklets();
  }
}

std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& ChunksManager::GetChunks() {
  return chunks_;
}

Block ChunksManager::GetBlock(glm::vec3 position) const {
  std::shared_ptr<Chunk> chunk = GetChunk(WorldPosToChunkPos(position));
  if (chunk == nullptr)
    return Block::kAir; //when chunkupdating done change this to kGround
  return chunk->GetBlock(position);
}

VectorXZ ChunksManager::WorldPosToChunkPos(glm::vec3 &world_pos) const {
  i64 chunkX = world_pos.x >= 0 ? world_pos.x / 16 : (world_pos.x - 15) / 16;
  i64 chunkZ = world_pos.z >= 0 ? world_pos.z / 16 : (world_pos.z - 15) / 16;
  return {chunkX, chunkZ};
}