#pragma once

#include "base_renderer.h"

class TranslucentRenderer : public BaseRenderer {
public:
  void Render(Camera &camera) override;
};