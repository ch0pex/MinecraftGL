#include "world.h"
#include "config/config.h"


World::World(Player& player) :
  chunks_manager_(*this),
  active_(true),
  player_(player)
{
  std::cout << "Loading world\n";
  world_loaders_.emplace_back([&]() { InitChunks();});
  world_loaders_.emplace_back([&]() {UpdateChunks();});
}

World::~World(){
  active_ = false;
  for(auto &loader : world_loaders_)
    loader.join();
}

void World::Update() {
  chunks_manager_.UpdateBufferedChunks(player_.GetPos());
}

void World::InitChunks() {
  for (i8 x = -kGameConfig.chunk_distance; x < kGameConfig.chunk_distance; x++) {
    for (i8 z = -kGameConfig.chunk_distance; z < kGameConfig.chunk_distance; z++) {
      if (!IsActive())
        return;
      std::unique_lock<std::mutex> lock(mutex_);
      chunks_manager_.AddChunk({x,z});
    }
  }

  std::cout << "Chunks generated \n";
  chunks_manager_.BuildChunksMesh();
  SetLoaded();
  std::cout << "Chunks loaded \n";
}

void World::UpdateChunks() {
  VectorXZ old_player_chunks_pos = chunks_manager_.WorldPosToChunkPos(player_.GetPos());
  VectorXZ current_player_chunk_pos = {};
  while(IsActive()){
    if(!IsLoaded())
      continue;
   current_player_chunk_pos = chunks_manager_.WorldPosToChunkPos(player_.GetPos());
    if (old_player_chunks_pos == current_player_chunk_pos)
      continue;
    UnloadChunks();
    LoadChunks(old_player_chunks_pos);
    old_player_chunks_pos = current_player_chunk_pos;
  }
  /*
  while(active_){
    //Determine if it was x or z or -x or -z

    //Load new in range chunks
    //Delete out of range chunks
    old_player_chunks_pos = current_player_chunk_pos;
  }
   */
}
void World::LoadChunks(VectorXZ offset) {

}

void World::UnloadChunks() {
  const VectorXZ player_chunk_pos = chunks_manager_.WorldPosToChunkPos(player_.GetPos());
  std::vector<VectorXZ> remove_chunks;
  f32 distance;
  for (auto& [chunk_pos, chunk] : chunks_manager_.GetChunks()) {
    distance = chunks_manager_.DistanceFromChunkToPlayer(chunk_pos, player_chunk_pos);
    if (distance >= kGameConfig.chunk_distance && !chunk->IsBuffered())
      remove_chunks.push_back(chunk_pos);
  }
  for(auto &chunk : remove_chunks)
    chunks_manager_.RemoveChunk(chunk);
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
    return Block::kDirt;
  return chunks_manager_.GetBlock(pos);
}

bool World::IsActive() { return active_; }

bool World::IsLoaded() { return loaded_; }

void World::SetLoaded() { loaded_ = true; }
