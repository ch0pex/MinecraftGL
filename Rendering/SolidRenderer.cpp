#include "SolidRenderer.h"
#include <iostream>

SolidRenderer::SolidRenderer(u32 _texture, u32 _shader) :
	shader(_shader),
	texture(_texture)
{
	std::cout << "Texture: " << texture << std::endl << "Shader: " << shader << std::endl;
	Mesh* mesh = new Mesh();
	std::vector<Vertex> _vertices = {

	{ { 0.0f, 0.0f,0.5f },{0.5f,0.5f,1.0 },{1.0f,0.5f,0.5 },{0.5,1.0 } },
	{ { 0.0f,1.0f,0.5f },{0.5f,0.5f,1.0 },{0.5f,1.0f,0.5 },{0.5,0.5 } },
	{ {1.0f,1.0f,0.5f },{0.5f,0.5f,1.0 },{0.5f,0.5f,1.0 },{1.0,0.5 } },
	{ {1.0f, 0.0f,0.5f },{0.5f,0.5f,1.0 },{1.0f,0.5f,1.0 },{1.0,1.0 } }
	};
	std::vector<uint32_t> _indices = {

	0, 1, 2,
	0, 2, 3
	};
	mesh->vertices = _vertices;
	mesh->indices = _indices;
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao);

	glGenBuffers(1, &mesh->vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	meshes.push_back(mesh); 
}

void SolidRenderer::add(Mesh* mesh)
{
	meshes.push_back(mesh); 
}

void SolidRenderer::render(Camera& camera)
{


	// Por cada cara en 
	glUseProgram(shader);
	/*
	glEnable(GL_POLYGON_MODE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	*/

	glm::mat4 vp = camera.getViewProjection();
	GLuint vpLoc = glGetUniformLocation(shader, "vp");
	glUniformMatrix4fv(vpLoc, 1, GL_FALSE, glm::value_ptr(vp));

	glBindTexture(GL_TEXTURE_2D, texture);
	
	std::cout << meshes.at(0)->indices.size() << std::endl; 
	
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


