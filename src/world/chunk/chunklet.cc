#include "chunklet.h"
#include "world/world.h"


Chunklet::Chunklet(World &world, glm::vec3 chunklet_position) :
    world_(&world),
    chunklet_position_(chunklet_position)
{
  model_.solid_mesh = Mesh();
  model_.water_mesh = Mesh();
  world_position_.x = chunklet_position_.x * kChunkSize;
  world_position_.y = chunklet_position_.y * kChunkSize;
  world_position_.z = chunklet_position_.z * kChunkSize;
  block_map_.reserve(kChunkletVolume);
}

Chunklet::~Chunklet() = default;

void Chunklet::BuildMesh() {
  for (int i = 0; i < kChunkletVolume; i++) {
    int x = i % kChunkSize;
    int y = i / (kChunkSize * kChunkSize);
    int z = (i / kChunkSize) % kChunkSize;
    //std::cout << "Block: " << x << ", " << y << ", " << z << std::endl;
    if (block_map_[i] != Block::kAir)
      AddBlockMesh(glm::vec3(world_position_.x + x, world_position_.y + y, world_position_.z + z), block_map_[i]);
  }

}


void Chunklet::AddBlockMesh(glm::vec3 position, Block block_type) {

  if (TryToAddFace(block_type, BlockFace::kFront, position))
    AddFace(position, kFaceFront, kBlockAtlasIds[block_type].front);

  if (TryToAddFace(block_type, BlockFace::kBack, position))
    AddFace(position, kFaceBack, kBlockAtlasIds[block_type].back);

  if (TryToAddFace(block_type, BlockFace::kRight, position))
    AddFace(position, kFaceRight, kBlockAtlasIds[block_type].right);

  if (TryToAddFace(block_type, BlockFace::kLeft, position))
    AddFace(position, kFaceLeft, kBlockAtlasIds[block_type].left);

  if (TryToAddFace(block_type, BlockFace::kTop, position))
    AddFace(position, kFaceTop, kBlockAtlasIds[block_type].top);

  if (TryToAddFace(block_type, BlockFace::kBottom, position))
    AddFace(position, kFaceBottom, kBlockAtlasIds[block_type].bottom);

}

void Chunklet::BufferMesh(Mesh &mesh) {

  if (mesh.render_info.faces == 0) return;
  glGenVertexArrays(1, &mesh.render_info.vao);
  glBindVertexArray(mesh.render_info.vao);

  glGenBuffers(1, &mesh.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh.vertices.size(), &mesh.vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &mesh.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh.indices.size(), &mesh.indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid *>(0));

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (offsetof(Vertex, Vertex::tex_coords)));

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (offsetof(Vertex, Vertex::normal)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
 /*
  mesh.vertices.clear();
  mesh.vertices.shrink_to_fit();
  mesh.indices.clear();
  mesh.indices.shrink_to_fit();
  */
}

void Chunklet::UnBufferMesh(Mesh &mesh) {
  glDeleteBuffers(1, &mesh.vbo);
  glDeleteBuffers(1, &mesh.ebo);
  glDeleteVertexArrays(1, &mesh.render_info.vao);
}
u32 Chunklet::GetFaces() const {
  return (model_.solid_mesh.render_info.faces + model_.water_mesh.render_info.faces);
}

void Chunklet::AddFace(glm::vec3 position, const Vertex face[], u32 face_texture_index) {
  Mesh *mesh_pointer;

  if (face_texture_index == 8) mesh_pointer = &model_.water_mesh;
  else mesh_pointer = &model_.solid_mesh;

  mesh_pointer->render_info.faces++;
  u32 index_offset = mesh_pointer->vertices.size();
  for (int i = 0; i < 6; i++) {
    if (i < 4) {
      Vertex vertex = face[i];
      vertex.position += position;
      vertex.tex_coords /= 16.0f;
      vertex.tex_coords.x += face_texture_index * 0.0625f;
      mesh_pointer->vertices.push_back(vertex);
    }
    mesh_pointer->indices.push_back(kFaceIndex[i] + index_offset);

  }
}

bool Chunklet::TryToAddFace(Block block_type, BlockFace block_face, glm::vec3 block_pos) {
  glm::vec3 offset = glm::vec3(0, 0, 0);
  switch (block_face) {
    case BlockFace::kFront:
      offset = glm::vec3(0, 0, 1);
      break;
    case BlockFace::kBack:
      offset = glm::vec3(0, 0, -1);
      break;
    case BlockFace::kRight:
      offset = glm::vec3(1, 0, 0);
      break;
    case BlockFace::kLeft:
      offset = glm::vec3(-1, 0, 0);
      break;
    case BlockFace::kTop:
      offset = glm::vec3(0, 1, 0);
      break;
    case BlockFace::kBottom:
      offset = glm::vec3(0, -1, 0);
      break;
    default:
      break;
  }

  offset += block_pos;

  Block block_next_to;
  //std::cout << OutOfBounds(offset) << "\n";
  if (OutOfBounds(offset))
    block_next_to = world_->GetBlock(offset);
  else
    block_next_to = GetBlock(offset);

  if (block_type == Block::kWater && block_next_to == Block::kAir)
    return true;
  if (block_type != Block::kWater && (block_next_to == Block::kAir || block_next_to == Block::kWater))
    return true;
  return false;
}


bool Chunklet::OutOfBounds(glm::vec3 block_pos) const {
  bool x = (block_pos.x >= world_position_.x && block_pos.x < world_position_.x + kChunkSize);
  bool y = (block_pos.y >= world_position_.y && block_pos.y < world_position_.y + kChunkSize);
  bool z = (block_pos.z >= world_position_.z && block_pos.z < world_position_.z + kChunkSize);
  return !(x && y && z);
}


Block Chunklet::GetBlock(glm::vec3 absolute_position) {
  int x = absolute_position.x - world_position_.x;
  int y = absolute_position.y - world_position_.y;
  int z = absolute_position.z - world_position_.z;
  int index = x + z * kChunkSize + y * kChunkSize * kChunkSize;

  return block_map_.at(index);

}

void Chunklet::SetBlock(Block block) {
  //TODO: Set block in chunk_position_
  block_map_.push_back(block);
}

