#pragma once

#include <vector>
#include <glm/glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#include "Camera.h"
#include "../common/public/CommonHeaders.h"


class MeshRenderer {

private:
	std::vector<Mesh*> meshes; 
	u32 texture, shader; 


public:
	MeshRenderer();
	~MeshRenderer();

	void setTexture(u32 _texture); 
	void setShader(u32 _shader); 

	void addMesh(Mesh* mesh);
	void render(Camera& camera);


	void addReferenceMesh();

};