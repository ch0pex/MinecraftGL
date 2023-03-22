#include "SolidRenderer.h"
#include <iostream>

SolidRenderer::SolidRenderer(u32 _texture, u32 _shader) :
	shader(_shader),
	texture(_texture)
{
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


