#pragma once
#include "../../rendering/Mesh.h"
#include <GL/glew.h>
#include "block.h"


class Chunklet {

private: 
	Block blockMap[CHUNK_VOLUME];
	 
	glm::vec3 position; 
	void addFace(glm::vec3 position, const Vertex face[]); 

public:
	Mesh* mesh;
	Chunklet(glm::vec3 _position);
	~Chunklet();
	void addBlock(glm::vec3 position); 
	void bufferMesh(); 
};