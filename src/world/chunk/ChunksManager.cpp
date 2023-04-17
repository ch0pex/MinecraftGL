#include "ChunksManager.h"
#include "../World.h"

ChunksManager::ChunksManager(World &_world) : 
    world(&_world)
{

    std::cout << "Chunks Loading... ";
    //TODO: load with threads chunks 8 to every direction at pos 0,0,0
    loadChunks(); 
    std::cout << "Done:" << chunks.size() << "loaded \n"; 



}


ChunksManager::~ChunksManager()
{
    
}


Chunk* ChunksManager::getChunk(glm::vec2 xzpos)
{

    glm::vec2 chunkPos; 
    chunkPos.x = ((int) xzpos.x / CHUNK_SIZE) * CHUNK_SIZE;
    chunkPos.y = ((int) xzpos.y / CHUNK_SIZE) * CHUNK_SIZE;

    //std::cout << chunkPos.x << ", " << chunkPos.y << "\n"; 
    //std::cout << "Numero de chunks: " << chunks.size() << "\n"; 
    for(auto& chunk : chunks){ 
        std::cout << chunk.getPosition().x << ", " << chunk.getPosition().y << "\n";
        if(chunk.getPosition() == chunkPos){
            return &chunk; 
        }
    }
    return nullptr; 
}


void ChunksManager::loadChunks()
{
    Timer t; 
    for (size_t x = 0; x < 10; x++)
    {
        for (size_t z = 0; z < 10; z++)
        {
            glm::vec2 pos = glm::vec2(x, z);
            std::vector<Block>* blocks = generator.genChunk(pos);
            chunks.push_back(Chunk(*world, pos, blocks));
            //chunk.loadChunklets(); 

        }
    }

    for(auto& chunk : chunks)
        chunk.loadChunklets();  
    

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
    if(chunk == nullptr) return Block::AIR; 
    return chunk->getBlock(position); 
}

