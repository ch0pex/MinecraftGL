#pragma once

#include "common/public/common_headers.h"
#include <GL/glew.h>

class TextureLoader {
public:
  static u32 LoadTexture(const std::string &file_name);
  static u32 LoadSkyTexture(const std::string faces[2]);
};