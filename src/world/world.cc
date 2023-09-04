#include "world.h"
#include "config/config.h"


World::World(Player& player) :
  chunks_manager_(*this),
  active_(true),
  player_(player)
{
  std::cout << "Loading world\n";
  world_loaders_.emplace_back([&]() { InitChunks();});
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
  for (i8 x = -kGameConfig.chunk_distance; x <= kGameConfig.chunk_distance; x++) {
    for (i8 z = -kGameConfig.chunk_distance; z <= kGameConfig.chunk_distance; z++) {
      if (!IsActive())
        return;
      std::unique_lock<std::mutex> lock(mutex_);
      chunks_manager_.AddChunk({x,z});
    }
  }

  std::cout << "Chunks generated \n";
  chunks_manager_.BuildChunksMesh();
  SetLoaded();
  LoadChunks();
  std::cout << "Chunks loaded \n";
}

void World::LoadChunks() { // If player moves out its current chunk, updates chunks
  //VectorXZ old_player_chunks_pos = chunks_manager_.WorldPosToChunkPos(player_.GetPos());
  //VectorXZ current_player_chunk_pos = {};
  while(IsActive()){
    //current_player_chunk_pos = chunks_manager_.WorldPosToChunkPos(player_.GetPos());
    //if (old_player_chunks_pos == current_player_chunk_pos)
      //continue;
    UpdateChunks();
    //old_player_chunks_pos = current_player_chunk_pos;
  }
}


void World::UpdateChunks() {
  const VectorXZ player_chunk_pos = chunks_manager_.WorldPosToChunkPos(player_.GetPos());
  const ChunkMap& chunks = chunks_manager_.GetChunks();
  f32 distance;
  for (ChunkMap::const_iterator itr = chunks.begin(); itr != chunks.end();){
    distance = chunks_manager_.DistanceFromChunkToPlayer(itr->first, player_chunk_pos);
    if (!itr->second->IsBuilt() && distance < kGameConfig.chunk_distance)
    {
      std::unique_lock<std::mutex> lock(mutex_);
      itr->second->BuildMesh();
    }
    else if (!itr->second->IsBuffered() && distance > kGameConfig.chunk_distance)
    {
      std::unique_lock<std::mutex> lock(mutex_);
      itr = chunks_manager_.RemoveChunk(itr);
      continue;
    }
    itr++;
  }
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
