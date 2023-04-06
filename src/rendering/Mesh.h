#pragma once
#include "../common/public/CommonHeaders.h"
#include <glm/glm/glm.hpp>
#include <vector>


struct Vertex{
	glm::vec3 position; 
	glm::vec3 normal;
	glm::vec3 color; 
	glm::vec2 texCoords; 
};

struct Mesh{
	u32 vao, vbo, ebo; 
	std::vector<Vertex> vertices;
	std::vector<u32> indices; 
};