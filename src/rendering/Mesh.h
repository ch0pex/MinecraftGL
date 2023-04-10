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


constexpr Vertex FACE_FRONT[4] = {
		{ { 0.0f , 0.0f ,1.0f  },{0.5f ,0.5f ,1.0f },{1.0f ,0.5f ,0.5f }, { 0.0f, 1.0f } },
		{ { 0.0f ,1.0f ,1.0f  },{0.5f ,0.5f ,1.0f },{0.5f ,1.0f ,0.5f },{ 0.0f, 0.0f } },
		{ {1.0f ,1.0f ,1.0f  },{0.5f ,0.5f ,1.0f },{0.5f ,0.5f ,1.0f }, { 1.0f, 0.0f } },
		{ {1.0f , 0.0f ,1.0f  },{0.5f ,0.5f ,1.0f },{1.0f ,0.5f ,1.0f },{ 1.0f, 1.0f } }
	};

constexpr Vertex FACE_BACK[4] = {
		{ {1.0f, 0.0f, 0.0f },{0.5f ,0.5f , 0.0f },{1.0f ,0.5f ,1.0f }, {0.0f, 1.0f } }, //4
		{ {1.0f ,1.0f, 0.0f },{0.5f ,0.5f , 0.0f },{0.5f ,1.0f ,1.0f }, {0.0f, 0.0f } }, //5
		{ { 0.0f,1.0f, 0.0f },{0.5f ,0.5f , 0.0f },{0.5f ,1.0f ,1.0f }, {1.0f, 0.0f } }, //6
		{ { 0.0f, 0.0f, 0.0f },{0.5f ,0.5f , 0.0f },{1.0f ,0.5f ,1.0f },{1.0f, 1.0f } }
};


constexpr Vertex FACE_LEFT[4] = {
		{ { 0.0f, 0.0f, 0.0f },{ 0.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },{0.0f, 1.0f } }, //8
		{ { 0.0f ,1.0f, 0.0f },{ 0.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },{0.0f, 0.0f } }, //9
		{ { 0.0f,1.0f,1.0f },{ 0.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },  {1.0f, 0.0f } },   //10
		{ { 0.0f, 0.0f,1.0f },{ 0.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f }, {1.0f, 1.0f } }//11
};

constexpr Vertex FACE_RIGHT[4] = {
		{ {1.0f, 0.0f,1.0f },{1.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },   {0.0f, 1.0f } }, // 12
		{ {1.0f ,1.0f,1.0f },{1.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },   {0.0f, 0.0f } }, //13
		{ {1.0f,1.0f, 0.0f },{1.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },   {1.0f, 0.0f } }, //14
		{ {1.0f, 0.0f, 0.0f },{1.0f ,0.5f ,0.5f },{0.5f ,0.5f ,1.0f },  {1.0f, 1.0f } } //15
};

constexpr Vertex FACE_TOP[4] = {
		{ { 0.0f ,1.0f ,1.0f  },{0.5f ,1.0f ,0.5f },{0.5f ,0.5f ,1.0f },{ 0.0f, 1.0f } }, //16
		{ { 0.0f ,1.0f , 0.0f  },{0.5f ,1.0f ,0.5f },{0.5f ,0.5f ,1.0f }, { 0.0f, 0.0f } }, //17
		{ {1.0f ,1.0f , 0.0f  },{0.5f ,1.0f ,0.5f },{0.5f ,0.5f ,1.0f },{ 1.0f, 0.0f } }, //18
		{ {1.0f ,1.0f ,1.0f  },{0.5f ,1.0f ,0.5f },{0.5f ,0.5f ,1.0f }, { 1.0f, 1.0f } } //19
};

constexpr Vertex FACE_BOTTOM[4] = {
		{ { 0.0f , 0.0f, 0.0f }, {0.5f , 0.0f ,0.5f }, {0.5f ,0.5f ,1.0f }, { 0.0f, 1.0f } }, //20
		{ { 0.0f, 0.0f,1.0f }, {0.5f , 0.0f ,0.5f },{0.5f ,0.5f ,1.0f }, { 0.0f, 0.0f } }, //21
		{ {1.0f, 0.0f,1.0f }, {0.5f , 0.0f ,0.5f },{0.5f ,0.5f ,1.0f },  { 1.0f, 0.0f } },  //22
		{ {1.0f, 0.0f, 0.0f }, {0.5f , 0.0f ,0.5f },{0.5f ,0.5f ,1.0f }, { 1.0f, 1.0f } } //23
};


constexpr u32 FACE_INDEX[6] = {
	0,1,2,
	0,2,3
};

