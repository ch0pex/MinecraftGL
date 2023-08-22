#pragma once

#include "rendering/mesh.h"
#include <GL/glew.h>
#include "block.h"


class World;

struct Model {
  Mesh solid_mesh;
  Mesh water_mesh;
  //flora_mesh;
};

class Chunklet {
public:
  Chunklet(World &world, glm::vec3 chunklet_position);
  ~Chunklet();

  void AddBlockMesh(glm::vec3 position, Block block_type);
  void BufferMesh(Mesh &mesh);
  void BuildMesh();

  u32 GetFaces() const;
  Block GetBlock(glm::vec3 absolute_position);
  void SetBlock(Block block);
  inline Model& GetModel() { return model_; }
  inline glm::vec3 GetPosition() const { return world_position_; }

private:
  void AddFace(glm::vec3 position, const Vertex face[], u32 face_texture_index);
  bool TryToAddFace(Block block_type, BlockFace block_face, glm::vec3 block_pos);
  bool OutOfBounds(glm::vec3 block_pos);

  World *world_;
  std::vector<Block> block_map_;
  glm::vec3 world_position_;
  glm::vec3 chunklet_position_;
  Model model_;
};
