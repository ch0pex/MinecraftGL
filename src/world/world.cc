#include "world.h"


World::World() :
	chunks_manager_(*this) 
{

}

World::~World()
{

}

void World::Update(Camera &camera)
{
	chunks_manager_.UpdateChunks(camera.GetPosition());
}

// Render prepare, load all meshes_ in their respective renderer
// Currently just solidrenderer
void World::PrepareRender(RenderEngine &renderer, Camera &camera) {
	// TODO: Render not more further than RENDER MAX DISTANCE
	for (auto &chunk: chunks_manager_.GetChunks()) {
		if (chunk.IsBuilded() && chunk.IsBuffered()) {
			chunk.DrawChunklets(renderer, camera); // Pass camera_
		}
	}
}


Block World::GetBlock(glm::vec3 pos) 
{
	//std::cout << pos.x << ", " << pos.y << ", " << pos.z << "\n";
	if (pos.y > 255 || pos.y < 0) {
		return Block::kAir;
	}
	return chunks_manager_.GetBlock(pos);
}

