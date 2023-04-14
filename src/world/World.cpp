#include "World.h"



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
		if(!chunk.isBuffered())
			chunk.drawChunklets(renderer); // Pass camera 
	}

}