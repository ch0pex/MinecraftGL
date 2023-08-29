#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "renderers/renderers.h"
#include "world/chunk/chunklet.h"


class RenderEngine {

public:
  RenderEngine();
  ~RenderEngine();
  void RenderScene(Camera &camera);
  void RenderLoadingScreen();
  bool ShouldClose();
  void DrawChunklet(Chunklet &chunklet);

  enum class MouseMode {
    kDisabled,
    kNormal,
    kHidden
  };

  void static Terminate();
  void SwapMouseMode(MouseMode mode);
  GLFWwindow *GetWindow();

private:
  void InitializeRenderers();
  GLFWwindow *window_;
  SolidRenderer solid_renderer_;
  TranslucentRenderer water_renderer_;
  SkyRenderer sky_renderer_;
};
