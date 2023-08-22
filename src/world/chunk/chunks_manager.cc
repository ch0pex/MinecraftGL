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

Chunk *ChunksManager::GetChunk(glm::vec2 xzpos) {
  glm::vec2 chunk_pos;
  chunk_pos.x = (int) (static_cast<int>(xzpos.x) / static_cast<int>(kChunkSize));
  chunk_pos.y = (int) (static_cast<int>(xzpos.y) / static_cast<int>(kChunkSize));
  if (xzpos.x < 0) chunk_pos.x -= 1;
  if (xzpos.y < 0) chunk_pos.y -= 1;

  for (auto &chunk: chunks_) {
    if (chunk.GetPosition().x == chunk_pos.x && chunk.GetPosition().y == chunk_pos.y) {
      return &chunk;
    }
  }
  return nullptr;
}

void ChunksManager::LoadChunks() {
  chunks_.reserve(24 * 24);
  for (i8 x = 0; x < 12; x++) {
    for (i8 z = 0; z < 12; z++) {
      if (!world_->IsActive())
        return;
      std::unique_lock<std::mutex> lock(mutex_);
      chunks_.emplace_back(*world_, glm::vec2(x , z));
    }
  }

  std::cout << "Chunks generated: " << chunks_.size() << "\n";
  BuildChunksMesh();
  std::cout << "Chunks loaded: " << chunks_.size() << "\n";
}

void ChunksManager::BuildChunksMesh() {
  std::cout << chunks_.size() << "\n";
  for (auto &chunk: chunks_) {
    if (!world_->IsActive()) return;
    chunk.BuildMesh();
  }
}

void ChunksManager::UpdateChunks(glm::vec3 player_pos) {
  //TODO: load and unload chunks_ depending on player_/cam chunk_position_
  for (auto &chunk: chunks_) {
    if (chunk.IsBuilt() && !chunk.IsBuffered())
      chunk.BufferChunklets();
  }
}

std::vector<Chunk>& ChunksManager::GetChunks() {
  return chunks_;
}

Block ChunksManager::GetBlock(glm::vec3 position) {
  Chunk *chunk = GetChunk(glm::vec2(position.x, position.z));
  if (chunk == nullptr)
    return Block::kAir; //when chunkupdating done change this to kGround
  return chunk->GetBlock(position);
}
