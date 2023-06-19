#pragma once

#include <vector>
#include <glm/glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "camera.h"
#include "../common/public/common_headers.h"


class MeshRenderer {

private:
	std::vector<RenderInfo*> meshes; 
	u32 texture, shader; 


public:
	MeshRenderer();
	~MeshRenderer();

	void setTexture(u32 _texture); 
	void setShader(u32 _shader); 

	void addMesh(RenderInfo* mesh);
	void render(Camera& camera);
	
	void addReferenceMesh();

};