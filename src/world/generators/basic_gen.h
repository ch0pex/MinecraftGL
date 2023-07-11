#pragma once

#include "../chunk/block.h"
#include <vector>
#include <glm/glm/glm.hpp>
#include "../chunk/chunk.h"


class BasicGen {
public:
    static void GenChunk(Chunk &chunk);
};
