#pragma once

#include <GL/glew.h>
#include <vector>

#include "../ThirdParty/glm/glm/glm.hpp"
#include "../ThirdParty/glm/glm/gtc/type_ptr.hpp"
#include "../Common/CommonHeaders.h"
#include "../Core/Chunk/Chunk.h"
#include "Camera.h"
#include "Mesh.h"

class SolidRenderer
{
private: 
	u32 shader, texture; 
	std::vector<u32> texturesID; 
	 
	std::vector<Mesh*> meshes; 

public: 
	SolidRenderer(u32 _shader, u32 _texture);
	void add(Mesh* mesh);
	void render(Camera &camera); 

};

