#include "Chunk.h"
#include "../World.h"

Chunk::Chunk(World& _world, glm::vec2 _position, std::vector<Block>* _blocks) : 
	world(&_world)
{

	position = _position; 

	for(int i = 0; i < CHUNK_SIZE; i++){
		chunklets.push_back(new Chunklet(*world, glm::vec3(position.x, i * 16, position.y)));
	}


}

Chunk::~Chunk()
{

}

bool Chunk::isBuffered()
{
	return buffered;
}


void Chunk::drawChunklets(RenderEngine& renderer)
{
	for(const auto& chunklet : chunklets){
		renderer.drawChunklet(*chunklet); 
	}
	buffered = true; 
}


Block Chunk::getBlock(glm::vec3 position)
{
	return Block::AIR; 
}

glm::vec2 Chunk::getPosition()
{
	return position; 
}

