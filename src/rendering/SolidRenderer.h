#pragma once

#include <vector>
#include "Mesh.h"
#include "Camera.h"


class SolidRenderer {

private:
	std::vector<Mesh*> meshes; 
public:
	SolidRenderer();
	~SolidRenderer();
	void addMesh(Mesh* mesh);
	void render(Camera& camera);	
};