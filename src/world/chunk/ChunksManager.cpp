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


void ChunksManager::loadSection(size_t start, size_t end)
{
    Timer t("loadChunks",TimerMode::MS);  
    for (size_t x = start; x < end; x++)
    {
        for (size_t z = start; z < end; z++)
        {
            glm::vec2 pos = glm::vec2(x, z);
            Chunk chunk = Chunk(*world, pos); 
            generator.genChunk(chunk); 
            std::unique_lock<std::mutex> lock(mutex); 
            chunks.push_back(chunk);
        }
    }
}

void ChunksManager::loadChunks()
{
    for(u8 i = 0; i < 4; i++)
        sectorLoaders.emplace_back([&] () {loadSection(CHUNK_SIZE * i , (CHUNK_SIZE * i) + CHUNK_SIZE); }); 

    for(auto& loader : sectorLoaders)
        loader.join();

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

