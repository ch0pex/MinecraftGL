#include "chunklet.h"
#include "../world.h"


Chunklet::Chunklet(World &world, glm::vec3 position) :
        world_(&world) {
    mesh_ = new Mesh();
    position_.x = position.x;
    position_.y = position.y;
    position_.z = position.z;
    block_map_.reserve(kChunkletVolume);

    /*
    for(int i = 0; i < kChunkletVolume; i++)
    {
        block_map_[i] = Block(Block::kStone);
    }


    for(int i = 0; i < kChunkletVolume; i++)
    {
        int cube = 0;
        if (block_map_[i] == Block::kStone)
            cube = 1;
        std::cout << cube << "\n";
    }
    */
}


Chunklet::~Chunklet() {
    //delete (mesh_);
}


void Chunklet::BuildMesh() {
    for (int i = 0; i < kChunkletVolume; i++) {

        int x = i % kChunkSize;
        int y = i / (kChunkSize * kChunkSize);
        int z = (i / kChunkSize) % kChunkSize;
        //std::cout << "Block: " << x << ", " << y << ", " << z << std::endl;
        if (block_map_[i] == Block::kStone)
            AddBlockMesh(glm::vec3(position_.x + x, position_.y + y, position_.z + z));
    }

}

glm::vec3 Chunklet::GetPosition() {
    return position_;
}


void Chunklet::AddBlockMesh(glm::vec3 position) {

    if (TryToAddFace(BlockFace::kFront, position))
        AddFace(position, kFaceFront);

    if (TryToAddFace(BlockFace::kBack, position))
        AddFace(position, kFaceBack);

    if (TryToAddFace(BlockFace::kRight, position))
        AddFace(position, kFaceRight);

    if (TryToAddFace(BlockFace::kLeft, position))
        AddFace(position, kFaceLeft);

    if (TryToAddFace(BlockFace::kTop, position))
        AddFace(position, kFaceTop);

    if (TryToAddFace(BlockFace::kBottom, position))
        AddFace(position, kFaceBottom);

}


void Chunklet::BufferMesh() {

    if (GetFaces() == 0) return;
    glGenVertexArrays(1, &mesh_->render_info.vao);
    glBindVertexArray(mesh_->render_info.vao);

    glGenBuffers(1, &mesh_->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, mesh_->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh_->vertices.size(), &mesh_->vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &mesh_->ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh_->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh_->indices.size(), &mesh_->indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid *>(0));

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (offsetof(Vertex, Vertex::tex_coords)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    mesh_->vertices.clear();
    mesh_->vertices.shrink_to_fit();
    mesh_->indices.clear();
    mesh_->indices.shrink_to_fit();
}

u32 Chunklet::GetFaces() {
    return mesh_->render_info.faces;
}


void Chunklet::AddFace(glm::vec3 position, const Vertex face[]) {
    mesh_->render_info.faces++;
    u32 index_offset = mesh_->vertices.size();
    for (int i = 0; i < 6; i++) {
        if (i < 4) {
            Vertex vertex = face[i];
            vertex.position += position;
            mesh_->vertices.push_back(vertex);
        }
        mesh_->indices.push_back(kFaceIndex[i] + index_offset);

    }
}


bool Chunklet::TryToAddFace(BlockFace block_face, glm::vec3 block_pos) {
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

    Block block;
    //std::cout << OutOfBounds(offset) << "\n";
    if (OutOfBounds(offset))
        block = world_->GetBlock(offset);
    else
        block = GetBlock(offset);

    if (block == Block::kAir)
        return true;
    return false;
}


bool Chunklet::OutOfBounds(glm::vec3 block_pos) {
    bool x = (block_pos.x >= position_.x && block_pos.x < position_.x + kChunkSize);
    bool y = (block_pos.y >= position_.y && block_pos.y < position_.y + kChunkSize);
    bool z = (block_pos.z >= position_.z && block_pos.z < position_.z + kChunkSize);
    return !(x && y && z);
}


Block Chunklet::GetBlock(glm::vec3 absolute_position) {
    int x = absolute_position.x - position_.x;
    int y = absolute_position.y - position_.y;
    int z = absolute_position.z - position_.z;
    int index = x + z * kChunkSize + y * kChunkSize * kChunkSize;
    return block_map_[index];

}

void Chunklet::SetBlock(Block block) {
    //TODO: Set block in position_
    block_map_.push_back(block);
}