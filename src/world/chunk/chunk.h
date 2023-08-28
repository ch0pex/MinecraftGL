#pragma once

#include "rendering/render_engine.h"
#include "chunklet.h"
#include "common/public/common_headers.h"


class World;


class Chunk {
public:

  Chunk(World &world, glm::vec2 position);
  ~Chunk();

  [[nodiscard]] bool IsBuffered() const;
  [[nodiscard]] bool IsBuilt() const;

  void BuildMesh();
  void BufferChunklets();
  void DrawChunklets(RenderEngine &renderer, Camera &camera);

  Block GetBlock(glm::vec3 position);
  Chunklet *GetChunklet(u8 ypos);
  glm::vec2 GetPosition();

private:
  World *world_;
  glm::vec2 chunk_position_;
  glm::vec2 world_position_;
  std::vector<Chunklet> chunklets_;
  bool buffered_, built_;
};