#include "ChunksManager.h"
#include "../World.h"

ChunksManager::ChunksManager(World &_world) : 
    world(&_world)
{

    std::cout << "Chunks Loading... \n";
    chunkLoader = std::thread([&] () {loadChunks(); });; 

}


ChunksManager::~ChunksManager()
{
    chunkLoader.join();
}


Chunk* ChunksManager::getChunk(glm::vec2 xzpos)
{

    glm::vec2 chunkPos; 
    chunkPos.x = (int) ((int) xzpos.x / (int) CHUNK_SIZE);
    chunkPos.y = (int) ((int) xzpos.y / (int) CHUNK_SIZE);
    if(xzpos.x < 0) chunkPos.x -= 1; 
    if(xzpos.y < 0) chunkPos.y -= 1; 
    
    //std::cout << "Pertenece al chunk: " << chunkPos.x << ", " << chunkPos.y << "\n"; 

    for(auto& chunk : chunks) {
        if(chunk.getPosition().x == chunkPos.x && chunk.getPosition().y == chunkPos.y){
            return &chunk;  
        }
    }
    return nullptr; 
}


void ChunksManager::loadSection(size_t Xstart, size_t Xend , size_t Zstart, size_t Zend)
{
    Timer t("(section)",TimerMode::MS);
    std::vector<Chunk> temp;
    temp.reserve(CHUNK_SIZE * CHUNK_SIZE); 
    for (size_t x = Xstart; x < Xend; x++)
    {
        for (size_t z = Zstart; z < Zend; z++)
        {
            glm::vec2 pos = glm::vec2(x, z);
            Chunk chunk = Chunk(*world, pos); 
            generator.genChunk(chunk); 
            //std::unique_lock<std::mutex> lock(mutex); 
            temp.push_back(chunk);
        }
    }
    chunks.insert(chunks.end(), temp.begin(), temp.end());
}

void ChunksManager::loadChunks()
{
    {
    Timer t("loadchunks",TimerMode::MS);
    chunks.reserve(CHUNK_SIZE * CHUNK_SIZE * 4); 
    sectorLoaders.emplace_back([&] () {loadSection(0, CHUNK_SIZE * 2, 0, CHUNK_SIZE * 2);});
    sectorLoaders.emplace_back([&](){loadSection(0, CHUNK_SIZE * 2, CHUNK_SIZE * 2, CHUNK_SIZE * 4);});
    sectorLoaders.emplace_back([&](){loadSection(CHUNK_SIZE * 2, CHUNK_SIZE * 4, 0, CHUNK_SIZE * 2);});
    sectorLoaders.emplace_back([&](){loadSection(CHUNK_SIZE * 2, CHUNK_SIZE * 4, CHUNK_SIZE * 2, CHUNK_SIZE * 4);});

    for(auto& loader : sectorLoaders)
        loader.join();
    }
    std::cout << "Chunks generated: " << chunks.size() << "\n"; 
    buildChunksMesh(); 
    std::cout << "Chunks loaded: " << chunks.size() << "\n"; 
}

void ChunksManager::buildChunksMesh()
{
    Timer t("buldMesh");
    std::cout << chunks.size() << "\n" ; 
    for(auto& chunk: chunks)
        chunk.buildMesh();
    
}


void ChunksManager::updateChunks(glm::vec3 playerPos)
{
   //TODO: load and unload chunks depending on player/cam position 

}


std::vector<Chunk>& ChunksManager::getChunks()
{
    // TODO: insert return statement here
    return chunks; 
}


Block ChunksManager::getBlock(glm::vec3 position)
{
    Chunk* chunk = getChunk(glm::vec2(position.x, position.z));  
    if(chunk == nullptr) {
        return Block::AIR;
    } 
    return chunk->getBlock(position);
}

