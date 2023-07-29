#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "renderers/renderers.h"
#include "world/chunk/chunklet.h"


class RenderEngine {
private:
  GLFWwindow *window_;
  SolidRenderer solid_renderer_;
  TranslucentRenderer water_renderer_;
  SkyRenderer sky_renderer_;
  void InitializeRenderers();

public:
  RenderEngine();
  ~RenderEngine();

  void RenderScene(Camera &camera);
  bool ShouldClose();

  void DrawChunklet(Chunklet &chunklet);
  GLFWwindow *GetWindow();

};
