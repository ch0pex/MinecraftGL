#pragma once

#include "world/chunk/block.h"
#include <vector>
#include <glm/glm/glm.hpp>
#include "world/chunk/chunk.h"
#include "world/chunk/chunks_manager.h"


class BasicGen {
public:
  static void GenChunk(ChunksManager &chunks_manager, u32 index);
  static void FlatGen(Chunk &chunk);
};
