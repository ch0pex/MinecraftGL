#pragma once
#include "../../rendering/Mesh.h"
#include <GL/glew.h>
#include "block.h"


class World; 

class Chunklet {

private: 
	World* world; 
	Block blockMap[CHUNKLET_VOLUME];
	glm::vec3 position; 
	u32 faces; 
	void addFace(glm::vec3 position, const Vertex face[]); 
	bool tryToAddFace(BlockFace blockFace, glm::vec3 position);
	
public:
	u32 getFaces(); 
	Mesh* mesh;
	Chunklet(World& world, glm::vec3 _position);
	~Chunklet();
	void addBlock(glm::vec3 position); 
	void bufferMesh(); 
	int getBlock(glm::vec3 absolutePosition); 
};