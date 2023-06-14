#include "Chunk.h"
#include "../World.h"

Chunk::Chunk(World& _world, glm::vec2 _position) : 
	world(&_world)
{
	position = _position; 
	buffered = false; 
	builded = false; 

	for(int i = 0; i < CHUNK_SIZE; i++){
		chunklets.push_back(new Chunklet(*world, glm::vec3(position.x * CHUNK_SIZE, i * CHUNK_SIZE, position.y * CHUNK_SIZE)));
	}	
}

Chunk::~Chunk()
{

}


void Chunk::buildMesh()
{
	//std::cout << chunklets.size() << "\n"; 
	for(auto& chunklet : chunklets) 
		chunklet->buildMesh(); 
	builded = true; 
}

void Chunk::bufferChunklets()
{
	for(auto chunklet : chunklets)
		chunklet->bufferMesh();
	buffered = true;
}

bool Chunk::isBuffered()
{
	return buffered;
}


bool Chunk::isBuilded()
{
	return builded; 
}


void Chunk::drawChunklets(RenderEngine& renderer, Camera& camera)
{
	for(const auto& chunklet : chunklets)
		if (chunklet->getFaces() && camera.inFrustrum(*chunklet)) // TODO:f chunklet in frustrum
			renderer.drawChunklet(*chunklet); 
}


Block Chunk::getBlock(glm::vec3 position)
{
	int index = static_cast<int>(position.y / 16); 
	//std::cout << index << ", " << chunklets.size() << std::endl; 
	return chunklets.at(index)->getBlock(position); 
}

glm::vec2 Chunk::getPosition()
{
	return position; 
}

Chunklet* Chunk::getChunklet(u8 Ypos) 
{
	return chunklets.at(Ypos / 16); 
}