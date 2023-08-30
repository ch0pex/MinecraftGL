#include "world.h"
#include "config/config.h"


World::World() :
  chunks_manager_(*this),
  active_(true)
{
  std::cout << "Loading world\n";
  world_loaders_.emplace_back([&]() {LoadChunks();});
}

World::~World(){
  active_ = false;
  for(auto &loader : world_loaders_)
    loader.join();
}

void World::Update(const glm::vec3& player_pos) {
  chunks_manager_.UpdateBufferedChunks(player_pos);
}

void World::LoadChunks() {
  for (i8 x = -kGameConfig.chunk_distance; x < kGameConfig.chunk_distance; x++) {
    for (i8 z = -kGameConfig.chunk_distance; z < kGameConfig.chunk_distance; z++) {
      if (!IsActive())
        return;
      std::unique_lock<std::mutex> lock(mutex_);
      chunks_manager_.AddChunk({x,z});
    }
  }

  std::cout << "Chunks generated \n";
  SetLoaded();
  chunks_manager_.BuildChunksMesh();
  std::cout << "Chunks loaded \n";
}

void World::UpdateChunks() {
  /*
  VectorXZ old_player_chunks_pos = WorldPosToChunkPos(player_pos_ref_);
  VectorXZ current_player_chunk_pos = {};
  while(active_){
    current_player_chunk_pos = WorldPosToChunkPos(player_pos_ref_);
    if (old_player_chunks_pos == current_player_chunk_pos)
      continue;
    //Determine if it was x or z or -x or -z

    //Load new in range chunks
    //Delete out of range chunks
    old_player_chunks_pos = current_player_chunk_pos;
  }
   */
}
// Render prepare, load all meshes_ in their respective renderer
// Currently just solidrenderer
void World::PrepareRender(RenderEngine &renderer, Camera &camera) {
  // TODO: Render not further than RENDER MAX DISTANCE
  for (auto& [chunk_pos, chunk]: chunks_manager_.GetChunks()) {
    if (chunk->IsBuilt() && chunk->IsBuffered()) {
      chunk->DrawChunklets(renderer, camera); // Pass camera_
    }
  }
}

Block World::GetBlock(glm::vec3 pos) {
  if (pos.y > 255 || pos.y < 0)
    return Block::kAir;
  return chunks_manager_.GetBlock(pos);
}

bool World::IsActive() { return active_; }

bool World::IsLoaded() { return loaded_; }

void World::SetLoaded() { loaded_ = true; }
