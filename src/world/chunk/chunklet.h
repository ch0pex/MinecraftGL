#pragma once

#include "../../rendering/mesh.h"
#include <GL/glew.h>
#include "block.h"


class World;


class Chunklet {

private:
    World *world_;
    std::vector<Block> block_map_; //Block block_map_[kChunkletVolume]
    glm::vec3 position_;

    void AddFace(glm::vec3 position, const Vertex face[]);
    bool TryToAddFace(BlockFace block_face, glm::vec3 block_pos);
    bool OutOfBounds(glm::vec3 block_pos);
public:
    Chunklet(World &world, glm::vec3 position);
    ~Chunklet();

    Mesh *mesh_;
    u32 GetFaces();

    Block GetBlock(glm::vec3 absolute_position);
    void SetBlock(Block block);

    void AddBlockMesh(glm::vec3 position);
    void BufferMesh();
    void BuildMesh();

    glm::vec3 GetPosition();
};