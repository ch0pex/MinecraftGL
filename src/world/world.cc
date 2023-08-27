#include "world.h"


World::World() :
  chunks_manager_(*this),
  active_(true){

}
World::~World(){
  active_ = false;
}

void World::Update(Player &player) {
  chunks_manager_.UpdateChunks(player.Get);
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
  //std::cout << pos.x << ", " << pos.y << ", " << pos.z << "\n";
  if (pos.y > 255 || pos.y < 0) {
    return Block::kAir;
  }
  return chunks_manager_.GetBlock(pos);
}

bool World::IsActive() { return active_; }