#pragma once

#include "rendering/render_engine.h"
#include "chunk/chunks_manager.h"
#include "player/player.h"

class World {

public:
  World();
  ~World();

  void Update(const glm::vec3 &player_pos);
  void PrepareRender(RenderEngine &renderer, Camera &camera);

  bool IsActive();
  bool IsLoaded();
  void SetLoaded();

  Block GetBlock(glm::vec3 pos);

private:
  void LoadChunks();
  void UpdateChunks();

  ChunksManager chunks_manager_;
  std::atomic<bool> active_;
  std::atomic<bool> loaded_;
  std::vector<std::thread> world_loaders_;
  std::mutex mutex_;
};
