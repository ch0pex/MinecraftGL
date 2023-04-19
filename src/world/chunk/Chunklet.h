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
	bool tryToAddFace(BlockFace blockFace, glm::vec3 blockPos);
	bool outOfBounds(glm::vec3 blockPos); 
public:
	Chunklet(World& world, glm::vec3 _position);
	~Chunklet();
	
	Mesh* mesh;
	u32 getFaces(); 
	Block getBlock(glm::vec3 absolutePosition); 

	void addBlockMesh(glm::vec3 position); 
	void bufferMesh();
	void buildMesh();  
	
};