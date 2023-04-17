#include "Chunk.h"
#include "../World.h"

Chunk::Chunk(World& _world, glm::vec2 _position, std::vector<Block>* _blocks) : 
	world(&_world)
{

	position = _position; 
	buffered = false; 
}

Chunk::~Chunk()
{

}

void Chunk::loadChunklets()
{
	for(int i = 0; i < CHUNK_SIZE; i++){
		chunklets.push_back(new Chunklet(*world, glm::vec3(position.x * CHUNK_SIZE, i * CHUNK_SIZE, position.y * CHUNK_SIZE)));
	}
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
	u8 index = (int) position.y / 16; 
	return chunklets.at(index)->getBlock(position); 
}

glm::vec2 Chunk::getPosition()
{
	return position; 
}

