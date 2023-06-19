#include "world.h"



World::World() : 
	chunksManager(*this)
{

}

World::~World() 
{

}


void World::update(Camera& camera)
{
	chunksManager.updateChunks(camera.getPosition());

}


// Render prepare, load all meshes in their respective renderer
// Currently just solidrenderer
void World::prepareRender(RenderEngine &renderer, Camera &camera)
{
	// TODO: Render not more further than RENDER MAX DISTANCE
	for (auto& chunk : chunksManager.getChunks()){
		if(chunk.isBuilded() && chunk.isBuffered()){
			chunk.drawChunklets(renderer,camera); // Pass camera 
		}
	}
}


Block World::getBlock(glm::vec3 pos)
{
	//std::cout << pos.x << ", " << pos.y << ", " << pos.z << "\n"; 
	if(pos.y > 255 || pos.y < 0){ 
		return Block::AIR; 
	}
	return chunksManager.getBlock(pos); 
}

