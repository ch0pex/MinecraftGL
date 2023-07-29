#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "player/player.h"


struct InputInfo{
  bool* keys;
  glm::vec2* mouse_pos;
  f32 frame_time;
  u16 PressedKeys() const;
  bool PressedKeysAreDiag() const;
};
