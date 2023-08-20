#include "chunk.h"
#include "world/world.h"
#include "world/generators/basic_gen.h"

Chunk::Chunk(World &world, glm::vec2 position) :
    world_(&world),
    position_(position)
  {
  buffered_ = false;
  built_ = false;

  chunklets_.reserve(16);
  for (int i = 0; i < kChunkSize; i++)
    chunklets_.emplace_back(*world_, glm::vec3(position.x * kChunkSize, i * kChunkSize, position.y * kChunkSize));
  BasicGen::GenChunk(*this);
}


Chunk::~Chunk() {
  /*for(auto chunklet : chunklets_)
      delete (chunklet); */
  std::cout << "Destructor de chunk" << std::endl;
}

void Chunk::BuildMesh() {
  //std::cout << chunklets_.size() << "\n";
  for (auto &chunklet: chunklets_)
    chunklet.BuildMesh();
  built_ = true;
}

void Chunk::BufferChunklets() {
  for (auto& chunklet: chunklets_) {
    chunklet.BufferMesh(chunklet.GetModel().solid_mesh);
    chunklet.BufferMesh(chunklet.GetModel().water_mesh);
  }
  buffered_ = true;
}

bool Chunk::IsBuffered() const {
  return buffered_;
}

bool Chunk::IsBuilt() const {
  return built_;
}

void Chunk::DrawChunklets(RenderEngine &renderer, Camera &camera) {
  for (auto& chunklet: chunklets_)
    if (chunklet.GetFaces() && camera.InFrustum(chunklet))
      renderer.DrawChunklet(chunklet);
}

Block Chunk::GetBlock(glm::vec3 position) {
  int index = static_cast<int>(position.y / 16);
  //std::cout << index << ", " << chunklets_.size() << std::endl;
  return chunklets_.at(index).GetBlock(position);
}

glm::vec2 Chunk::GetPosition() {
  return position_;
}

Chunklet *Chunk::GetChunklet(u8 ypos) {
  return &chunklets_.at(ypos / 16);
}