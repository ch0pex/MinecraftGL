#include "chunks_manager.h"
#include "../world.h"
#include "../../config/config.h"


ChunksManager::ChunksManager(World &world) :
        world_(&world) {
    std::cout << "Chunks Loading... \n";
    chunk_loaders_.emplace_back([&]() { LoadChunks(); });
}

ChunksManager::~ChunksManager()
{
    for (auto &thread: chunk_loaders_)
        thread.join();
}

Chunk *ChunksManager::GetChunk(glm::vec2 xzpos)
{
    glm::vec2 chunk_pos;
    chunk_pos.x = (int) (static_cast<int>(xzpos.x) / static_cast<int>(kChunkSize));
    chunk_pos.y = (int) (static_cast<int>(xzpos.y) / static_cast<int>(kChunkSize));
    if (xzpos.x < 0) chunk_pos.x -= 1;
    if (xzpos.y < 0) chunk_pos.y -= 1;

    for (auto &chunk: chunks_) {
        if (chunk.GetPosition().x == chunk_pos.x && chunk.GetPosition().y == chunk_pos.y) {
            return &chunk;
        }
    }
    return nullptr;
}

void ChunksManager::LoadChunks()
{
    {
        Timer t("LoadChunks", TimerMode::kMs);
        chunks_.reserve(kGameConfig.chunk_distance);
        for (size_t x = 0; x < kGameConfig.chunk_distance; x++) {
            for (size_t z = 0; z < kGameConfig.chunk_distance; z++) {
                glm::vec2 pos = glm::vec2(x, z);
                Chunk chunk = Chunk(*world_, pos);
                BasicGen::GenChunk(chunk);
                std::unique_lock<std::mutex> lock(mutex_);
                chunks_.push_back(chunk);
            }
        }
    }


    std::cout << "Chunks generated: " << chunks_.size() << "\n";
    BuildChunksMesh();
    std::cout << "Chunks loaded: " << chunks_.size() << "\n";
}

void ChunksManager::BuildChunksMesh()
{
    Timer t("buldMesh");
    std::cout << chunks_.size() << "\n";
    for (auto &chunk: chunks_)
        chunk.BuildMesh();

}

void ChunksManager::UpdateChunks(glm::vec3 player_pos)
{
    //TODO: load and unload chunks_ depending on player/cam position_
    for (auto &chunk: chunks_) {
        if (chunk.IsBuilded() && !chunk.IsBuffered())
            chunk.BufferChunklets();
    }
}

std::vector<Chunk> &ChunksManager::GetChunks()
{
    // TODO: insert return statement here
    return chunks_;
}

Block ChunksManager::GetBlock(glm::vec3 position)
{
    Chunk *chunk = GetChunk(glm::vec2(position.x, position.z));
    if (chunk == nullptr)
        return Block::kAir;
    return chunk->GetBlock(position);
}
