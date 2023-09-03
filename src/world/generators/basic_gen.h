#pragma once

#include "world/chunk/block.h"
#include <vector>
#include <glm/glm/glm.hpp>
#include "world/chunk/chunk.h"


class BasicGen {
public:
  static void GenChunk(Chunk &chunk);
  static void FlatGen(Chunk &chunk);
};
