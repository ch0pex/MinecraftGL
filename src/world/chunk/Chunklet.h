#pragma once
#include "../../rendering/Mesh.h"
#include <GL/glew.h>
#include "block.h"


class Chunklet {

private: 
	Block blockMap[CHUNKLET_VOLUME];
	glm::vec3 position; 
	void addFace(glm::vec3 position, const Vertex face[]); 
	bool tryToAddFace(BlockFace blockFace, glm::vec3 position);
	
public:
	u32 getFaces(); 
	Mesh* mesh;
	Chunklet(glm::vec3 _position);
	~Chunklet();
	void addBlock(glm::vec3 position); 
	void bufferMesh(); 
};