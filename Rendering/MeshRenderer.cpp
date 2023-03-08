#include "MeshRenderer.h"


MeshRenderer::MeshRenderer(GameObject* gameObject, Camera* _camera, MeshType meshType)
{
	setGameObject(gameObject); 
	
	modelMatrix = glm::mat4(1.0f); 
	camera = _camera;
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
	position = glm::vec3(0.0f, 0.0f, 0.0f); 
	rotation = glm::vec3(0.0f, 0.0f, 0.0f); 

	switch (meshType) {
	case MeshType::CUBE: Mesh::setCubeData(vertices, indices); break; 
	case MeshType::OBJ:break; 
	case MeshType::SPHERE: Mesh::setSphereData(vertices, indices); break; 
	default:Mesh::setPlaneData(vertices, indices); break; 
	}
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 

	
}




void MeshRenderer::calculateModelMatrix()
{
	Transform* transform = gameObject->transform; 

	glm::mat4 rotationTranslationMatrix, scaleMatrix; 
	scaleMatrix = glm::scale(glm::mat4(1.0f), scale);

	rotationTranslationMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationTranslationMatrix = glm::rotate(rotationTranslationMatrix, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationTranslationMatrix = glm::rotate(rotationTranslationMatrix, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	rotationTranslationMatrix = glm::translate(glm::mat4(1.0f), position);
	rotationTranslationMatrix = glm::rotate(rotationTranslationMatrix, transform->getRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationTranslationMatrix = glm::rotate(rotationTranslationMatrix, transform->getRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationTranslationMatrix = glm::rotate(rotationTranslationMatrix, transform->getRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
	rotationTranslationMatrix = glm::translate(rotationTranslationMatrix, transform->getPosition());
	modelMatrix = scaleMatrix * rotationTranslationMatrix;
}


void MeshRenderer::update()
{
	calculateModelMatrix();
	glUseProgram(program);
	glm::mat4 vpm = camera->getProjection() * camera->getView() * modelMatrix;
	GLuint vpmLoc = glGetUniformLocation(program, "vpm");
	glUniformMatrix4fv(vpmLoc, 1, GL_FALSE, glm::value_ptr(vpm));

	glBindTexture(GL_TEXTURE_2D, texture);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}


void MeshRenderer::setProgram(GLuint _program)
{
	program = _program;
}

void MeshRenderer::setTexture(GLuint _texture)
{
	texture = _texture;
}

void MeshRenderer::setPosition(glm::vec3 _position)
{
	
	position = _position;
	calculateModelMatrix();
}

void MeshRenderer::setScale(glm::vec3 _scale)
{
	scale = _scale;
	calculateModelMatrix();
}

void MeshRenderer::setRotation(glm::vec3 _rotation)
{
	rotation = _rotation;
	calculateModelMatrix(); 
}

MeshRenderer::~MeshRenderer()
{

}