#pragma once

#include "rendering/render_engine.h"
#include "chunk/chunks_manager.h"
#include "rendering/camera.h"


class World {

public:
  World();
  ~World();

  void Update(Camera &camera);
  void PrepareRender(RenderEngine &renderer, Camera &camera);
  bool IsActive();
  Block GetBlock(glm::vec3 pos);

private:
  ChunksManager chunks_manager_;
  std::atomic<bool> active_;
};
