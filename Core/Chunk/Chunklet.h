/*16x16x16*/

#pragma once
 

#include <GL/glew.h>
#include "../../Common/CommonHeaders.h"
#include "../Block/Block.h"
#include "../../Rendering/Mesh.h"


class Chunklet
{
private: 
	glm::vec3 position; 
	Mesh solidMesh; 
	std::vector<Block> &blocksLayout; 
	void addBlock(glm::vec3 blockPos, u32 index);
	void addFace(glm::vec3 blockPos, Vertex face[4], u32 index);
	void bufferChunklet(); 

public: 
	Chunklet(glm::vec3 _position, std::vector<Block> &blocks);
	// CHECK: inline performance 
	inline u32 getFaces() { return (solidMesh.indices.size() / 6); }
	inline Mesh *getSolidMesh() { return &solidMesh; }
};

