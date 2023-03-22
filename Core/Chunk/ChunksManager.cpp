
#include "ChunksManager.h"

ChunksManager::ChunksManager()
{
    //TODO: load with threads chunks 8 to every direction at pos 0,0,0
  
    for (size_t x = 0; x < 1; x++)
    {
        for (size_t z = 0; z < 1; z++)
        {
            glm::vec2 pos = glm::vec2( x, z );
            std::vector<Block>* blocks = generator.genChunk(pos); 
            chunks.push_back(Chunk(pos, blocks));
        }
    }

}

Chunk ChunksManager::getChunk(glm::vec2 xypos)
{
    
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
