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




Chunk& ChunksManager::getChunk(glm::vec2 xypos)
{
    for(auto& chunk : chunks){ 
        if(chunk.getPosition() == xypos)
            return const_cast<Chunk&>(chunk); 
    }
}


void ChunksManager::loadChunks()
{
    for (size_t x = 0; x < 1; x++)
    {
        for (size_t z = 0; z < 1; z++)
        {
            glm::vec2 pos = glm::vec2(x, z);
            std::vector<Block>* blocks = generator.genChunk(pos); 
            chunks.push_back(Chunk(*world, pos, blocks));
        }
    }

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
    Chunk& chunk = getChunk(glm::vec2(position.x, position.y)); 
    return chunk.getBlock(position); 
}

