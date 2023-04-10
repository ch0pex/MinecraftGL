#include "SolidRenderer.h"
#include "../world/chunk/chunklet.h"

SolidRenderer::SolidRenderer() 
{
	


}

SolidRenderer::~SolidRenderer() 
{

}

void SolidRenderer::addMesh(/*Mesh* mesh*/)
{
	/*
	Mesh* mesh = new Mesh(); 
	std::vector<Vertex> _vertices = {

		//front
		{ { -1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0, 1.0 } },
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 },{ 0.0, 0.0 } },
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },
		{ { 1.0f, -1.0f, 1.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 1.0 },{ 1.0, 1.0 } },

		// back 
		{ { 1.0, -1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 1.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //4
		{ { 1.0f, 1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 0.0f, 1.0f, 1.0 },{ 0.0, 0.0 } }, //5
		{ { -1.0, 1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 0.0f, 1.0f, 1.0 },{ 1.0, 0.0 } }, //6
		{ { -1.0, -1.0, -1.0 },{ 0.0f, 0.0f, -1.0 },{ 1.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //7


		//left
		{ { -1.0, -1.0, -1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //8
		{ { -1.0f, 1.0, -1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //9
		{ { -1.0, 1.0, 1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },   //10
		{ { -1.0, -1.0, 1.0 },{ -1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //11

		//right
		{ { 1.0, -1.0, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, // 12
		{ { 1.0f, 1.0, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //13
		{ { 1.0, 1.0, -1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } }, //14
		{ { 1.0, -1.0, -1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //15

		//top
		{ { -1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //16
		{ { -1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //17
		{ { 1.0f, 1.0f, -1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } }, //18
		{ { 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //19

		//bottom 
		{ { -1.0f, -1.0, -1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 1.0 } }, //20
		{ { -1.0, -1.0, 1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 0.0, 0.0 } }, //21
		{ { 1.0, -1.0, 1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },  //22
		{ { 1.0, -1.0, -1.0 },{ 0.0f, -1.0f, 0.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }, //23

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


	mesh->vertices.clear(); mesh->indices.clear();
	mesh->vertices = _vertices;
	mesh->indices = _indices;
	std::cout << mesh->vertices.size() << std::endl; 
	std::cout << mesh->indices.size() << std::endl; 

	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao); 

	glGenBuffers(1, &mesh->vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); 

	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords))); 

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	meshes.push_back(mesh); 

	*/

	Chunklet* chunk[4][4][4]; 

	for(int i = 0; i < 4 ; i++){
		for(int j = 0; j < 4; j++){
			for(int k = 0; k < 4; k++){
				chunk[i][j][k] = new Chunklet(glm::vec3(j,k,i)); 
				chunk[i][j][k]->bufferMesh(); 
				meshes.push_back(chunk[i][j][k]->mesh);
			}	
		}

	}

}

void SolidRenderer::render(Camera& camera)
{


	glUseProgram(shader); 

	u32 vpLoc = glGetUniformLocation(shader, "vp");
	glm::mat4 vp = camera.getProjection() * camera.getView();

	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));
	glBindTexture(GL_TEXTURE_2D, texture);



	for(const auto& mesh : meshes){
		glBindVertexArray(mesh->vao); 
		glDrawElements(GL_TRIANGLES, mesh->indices.size(), GL_UNSIGNED_INT, 0); 
		glBindVertexArray(0); 

	} 

}

void SolidRenderer::setTexture(u32 _texture)
{
	texture = _texture; 
}

void SolidRenderer::setShader(u32 _shader)
{
	shader = _shader; 
}
