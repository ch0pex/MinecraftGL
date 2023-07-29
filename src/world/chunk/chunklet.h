#pragma once

#include "rendering/mesh.h"
#include <GL/glew.h>
#include "block.h"


class World;

struct Model {
  Mesh *solid_mesh;
  Mesh *water_mesh;
  //flora_mesh;
};

class Chunklet {
private:
  World *world_;
  std::vector<Block> block_map_; //Block block_map_[kChunkletVolume]
  glm::vec3 position_;

  void AddFace(glm::vec3 position, const Vertex face[], u32 face_texture_index);
  bool TryToAddFace(Block block_type, BlockFace block_face, glm::vec3 block_pos);
  bool OutOfBounds(glm::vec3 block_pos);
public:
  Chunklet(World &world, glm::vec3 position);
  ~Chunklet();

  Model model_;
  u32 GetFaces();

  Block GetBlock(glm::vec3 absolute_position);
  void SetBlock(Block block);
  void AddBlockMesh(glm::vec3 position, Block block_type);
  void BufferMesh(Mesh &mesh);
  void BuildMesh();

  glm::vec3 GetPosition();
};
