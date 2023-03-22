#pragma once
#include "../Thirdparty/glm/glm/glm.hpp"
#include <vector>
#include "../Common/CommonHeaders.h"


struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texCoords;
};


/*
std::vector<uint32_t> indices = {

	0, 1, 2,
	2, 3, 0,

	4, 5, 6,
	4, 6, 7,

	8, 9, 10,
	8, 10, 11,

	12, 13, 14,
	12, 14, 15,

	16, 17, 18,
	16, 18, 19,

	20, 21, 22,
	20, 22, 23

};

*/

struct Mesh {
	u32 vao, vbo, ebo; 
	std::vector<Vertex> vertices;
	std::vector<u32> indices;
};