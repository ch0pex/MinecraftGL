#include "SolidRenderer.h"
#include <iostream>

SolidRenderer::SolidRenderer(u32 _texture, u32 _shader) :
	shader(_shader),
	texture(_texture)
{

	static Mesh *mesh = new Mesh(); 
	std::vector<Vertex> _vertices = {

		//front
		{ { 0.0f, 0.0f,1.0f },{0.5f,0.5f,1.0 },{1.0f,0.5f,0.5 }, { 0.0, 1.0 } },
		{ { 0.0f,1.0f,1.0f },{0.5f,0.5f,1.0 },{0.5f,1.0f,0.5 },{ 0.0, 0.0 } },
		{ {1.0f,1.0f,1.0f },{0.5f,0.5f,1.0 },{0.5f,0.5f,1.0 }, { 1.0, 0.0 } },
		{ {1.0f, 0.0f,1.0f },{0.5f,0.5f,1.0 },{1.0f,0.5f,1.0 },{ 1.0, 1.0 } },

		// back 
		{ {1.0, 0.0, 0.0 },{0.5f,0.5f, 0.0 },{1.0f,0.5f,1.0 }, {0.0, 1.0 } }, //4
		{ {1.0f,1.0, 0.0 },{0.5f,0.5f, 0.0 },{0.5f,1.0f,1.0 }, {0.0, 0.0 } }, //5
		{ { 0.0,1.0, 0.0 },{0.5f,0.5f, 0.0 },{0.5f,1.0f,1.0 }, {1.0, 0.0 } }, //6
		{ { 0.0, 0.0, 0.0 },{0.5f,0.5f, 0.0 },{1.0f,0.5f,1.0 },{1.0, 1.0 } }, //7


		//left												    
		{ { 0.0, 0.0, 0.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },{0.0, 1.0 } }, //8
		{ { 0.0f,1.0, 0.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },{0.0, 0.0 } }, //9
		{ { 0.0,1.0,1.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },  {1.0, 0.0 } },   //10
		{ { 0.0, 0.0,1.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 }, {1.0, 1.0 } }, //11

		//right												    
		{ {1.0, 0.0,1.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {0.0, 1.0 } }, // 12
		{ {1.0f,1.0,1.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {0.0, 0.0 } }, //13
		{ {1.0,1.0, 0.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {1.0, 0.0 } }, //14
		{ {1.0, 0.0, 0.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },  {1.0, 1.0 } }, //15

		//top
		{ { 0.0f,1.0f,1.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 },{ 0.0, 1.0 } }, //16
		{ { 0.0f,1.0f, 0.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 0.0 } }, //17
		{ {1.0f,1.0f, 0.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 },{ 1.0, 0.0 } }, //18
		{ {1.0f,1.0f,1.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 }, { 1.0, 1.0 } }, //19

		//bottom 
		{ { 0.0f, 0.0, 0.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 1.0 } }, //20
		{ { 0.0, 0.0,1.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 0.0 } }, //21
		{ {1.0, 0.0,1.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 },  { 1.0, 0.0 } },  //22
		{ {1.0, 0.0, 0.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 1.0, 1.0 } }, //23

	};



	std::vector<uint32_t> _indices = {

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




	std::cout << shader << std::endl;
	std::cout << texture << std::endl;



	mesh->vertices = _vertices;
	mesh->indices = _indices;

	std::cout << "Mehs vao address: " << &mesh->vao << std::endl;
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	std::cout << "Mehs vbo address: " << &mesh->vao << std::endl;
	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	std::cout << "Mesh ebo address: " << &mesh->ebo << std::endl;
	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->indices .size(), &mesh->indices [0], GL_STATIC_DRAW);


	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	meshes.push_back(mesh); 
	std::cout << "Number of meshes: " << meshes.size() << std::endl;

}

void SolidRenderer::add(Mesh* mesh)
{
	meshes.push_back(mesh); 
}

void SolidRenderer::render(Camera& camera)
{


	glUseProgram(shader);
	glm::mat4 vp = camera.getViewProjection();
	std::cout << vp[0][0] << ", " << vp[0][1] << ", " << vp[0][2] << ", " << vp[0][3] << std::endl;
	GLuint vpLoc = glGetUniformLocation(shader, "viewProjMatrix");
	//std::cout << "Value_ptr: " << glm::value_ptr(camera.getViewProjection()) << std::endl;

	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

	glBindTexture(GL_TEXTURE_2D, texture);
	
	
	
	for (Mesh* mesh : meshes) {
		/*
		for (Vertex vertice : mesh->vertices) {
			std::cout << vertice.position.x << ", " << vertice.position.y << std::endl;
		}*/
		glBindVertexArray(mesh->vao);
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}


