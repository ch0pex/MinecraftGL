#include "World.h"



World::World(Camera &camera) :
	chunksDistance(8), 
	camera(camera)

{
	chunksManager = new ChunksManager(); 
}

World::~World()
{
	delete(chunksManager);
}


// Compute chunks 
void World::update()
{
	chunksManager->updateChunks(camera.getPosition()); 
}



// Render prepare, load all meshes in their respective renderer
// Currently just solidrenderer
void World::prepareRender(RenderEngine &renderer, Camera &camera)
{
	// TODO: Render not more further than RENDER MAX DISTANCE
	

	for (auto& chunk : chunksManager->getChunks()){
		if(!chunk.isBuffered())
			chunk.drawChunklets(renderer); // Pass camera 
	}

}
