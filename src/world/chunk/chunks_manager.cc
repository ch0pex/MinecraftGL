#include "chunks_manager.h"
#include "world/world.h"
#include "config/config.h"


ChunksManager::ChunksManager(World &world) :
    world_(&world) {
  std::cout << "Chunks Loading... \n";
  chunk_loaders_.emplace_back([&]() { LoadChunks(); });
}

ChunksManager::~ChunksManager() {
  for (auto &thread: chunk_loaders_)
    thread.join();
}

std::shared_ptr<Chunk> ChunksManager::GetChunk(glm::vec2 xzpos) {
  i64 chunkX = xzpos.x >= 0 ? xzpos.x / 16 : (xzpos.x - 15) / 16;
  i64 chunkZ = xzpos.y >= 0 ? xzpos.y / 16 : (xzpos.y - 15) / 16;
  VectorXZ chunk_pos = {chunkX, chunkZ};
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

void ChunksManager::UpdateChunks(glm::vec3 player_pos) {
  //TODO: load and unload chunks_ depending on player_/cam chunk_position_


  for (auto& [chunk_pos, chunk] : chunks_) {
    if (chunk->IsBuilt() && !chunk->IsBuffered())
      chunk->BufferChunklets();
  }
}

std::unordered_map<VectorXZ, std::shared_ptr<Chunk>>& ChunksManager::GetChunks() {
  return chunks_;
}

Block ChunksManager::GetBlock(glm::vec3 position) {
  std::shared_ptr<Chunk> chunk = GetChunk(position);
  if (chunk == nullptr)
    return Block::kAir; //when chunkupdating done change this to kGround
  return chunk->GetBlock(position);
}
