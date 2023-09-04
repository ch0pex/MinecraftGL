#include "chunk.h"
#include "world/world.h"
#include "world/generators/basic_gen.h"

Chunk::Chunk(World &world, const VectorXZ &position) :
    world_(&world),
    chunk_position_(position),
    world_position_({position.x * kChunkSize, position.z * kChunkSize}),
    buffered_(false),
    built_(false)
  {
  chunklets_.reserve(kChunkSize);
  for (int i = 0; i < kChunkSize; i++)
    chunklets_.emplace_back(*world_, glm::vec3(chunk_position_.x, i, chunk_position_.z));
  BasicGen::GenChunk(*this);
  //std::cout << "Generating chunk\n";
}

Chunk::~Chunk() {
  //std::cout << "Destroying chunk\n";
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

void Chunk::UnBufferChunklets() {
  for(auto& chunklet: chunklets_) {
    chunklet.UnBufferMesh(chunklet.GetModel().solid_mesh);
    chunklet.UnBufferMesh(chunklet.GetModel().water_mesh);
  }
  buffered_ = false;
  //std::cout << "Unbuffering Chunklet\n";
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

Block Chunk::GetBlock(const glm::vec3 &position) {
  int index = static_cast<int>(position.y / 16);
  //std::cout << index << ", " << chunklets_.size() << std::endl;
  return chunklets_.at(index).GetBlock(position);
}

VectorXZ Chunk::GetPosition() {
  return chunk_position_;
}

Chunklet *Chunk::GetChunklet(u8 ypos) {
  return &chunklets_.at(ypos / 16);
}

