#pragma once

#include "rendering/render_engine.h"
#include "chunklet.h"
#include "common/public/common_headers.h"
#include "math/vector_xz.h"


class World;


class Chunk {
public:

  Chunk(World &world, const VectorXZ &position);
  ~Chunk();

  bool IsBuffered() const;
  bool IsBuilt() const;

  void BuildMesh();
  void BufferChunklets();
  void UnBufferChunklets();
  void DrawChunklets(RenderEngine &renderer, Camera &camera);

  Block GetBlock(const glm::vec3 &position);
  Chunklet *GetChunklet(u8 ypos);
  VectorXZ GetPosition();

private:
  World *world_;
  VectorXZ chunk_position_;
  std::vector<Chunklet> chunklets_;
  std::atomic<bool> buffered_, built_;
};