#pragma once

#include "rendering/render_engine.h"
#include "chunk/chunks_manager.h"
#include "player/player.h"

class World {

public:
  World(Player& player);
  ~World();

  void Update();
  void PrepareRender(RenderEngine &renderer, Camera &camera);

  bool IsActive();
  bool IsLoaded();
  void SetLoaded();

  Block GetBlock(glm::vec3 pos);

private:
  void InitChunks();
  void LoadChunks();
  void UpdateChunks();

  Player& player_;
  ChunksManager chunks_manager_;
  std::atomic<bool> active_;
  std::atomic<bool> loaded_;
  std::mutex mutex_;
  std::vector<std::thread> world_loaders_;
};
