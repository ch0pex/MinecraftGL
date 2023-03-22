#include "Chunk.h"
#include "../../Rendering/RenderEngine.h"

Chunk::Chunk(glm::vec2 _position, std::vector<Block>* blocks) :
	position(_position),
	buffered(false)
{

	for (size_t i = 0; i < CHUNK_VOLUME; i += CHUNKLET_VOLUME)
	{
		std::vector<Block> chunkletMap(blocks->begin() + i, blocks->begin() + i + CHUNKLET_VOLUME);
		//std::cout << "hola: " << position.x << ", " << (i / 16) / 16 << ", " << position.y << std::endl;
		chunklets.push_back(new Chunklet(glm::vec3(position.x, (i / 16) / 16, position.y), chunkletMap));
	}
}

Chunk::~Chunk()
{
}


//For each chunklet, we need to get its meshesh and add it to the respective renderer
void Chunk::drawChunklets(RenderEngine &renderer)
{
	
	for(Chunklet* chunklet : chunklets) {
		renderer.drawChunklet(*chunklet); // TODO: Just draw chunklets inside culling camera 
	}
	buffered = true; 
}


