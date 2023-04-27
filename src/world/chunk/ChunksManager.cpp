#include "ChunksManager.h"
#include "../World.h"

ChunksManager::ChunksManager(World &_world) : 
    world(&_world)
{

    std::cout << "Chunks Loading... \n";
    chunkLoaders.emplace_back([&] () {loadChunks(); }); 

}


ChunksManager::~ChunksManager()
{
    for(auto& thread : chunkLoaders)
        thread.join();
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


void ChunksManager::loadChunks()
{
    {
    Timer t("loadChunks",TimerMode::MS);  
    for (size_t x = 0; x < CHUNK_SIZE * 2; x++)
    {
        for (size_t z = 0; z < CHUNK_SIZE * 2; z++)
        {
            glm::vec2 pos = glm::vec2(x, z);
            Chunk chunk = Chunk(*world, pos); 
            generator.genChunk(chunk); 
            //std::unique_lock<std::mutex> lock(mutex); 
            chunks.push_back(chunk);
        }
    }
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

