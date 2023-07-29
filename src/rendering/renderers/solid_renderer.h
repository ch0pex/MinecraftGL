#pragma once

#include "base_renderer.h"

class SolidRenderer : public BaseRenderer {
public:
  void Render(Camera &camera) override;
};