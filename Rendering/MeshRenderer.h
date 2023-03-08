#pragma once
#include <vector>
#include <thread>
#include <GL/glew.h>
#include "Mesh.h"
#include "Camera.h"
#include "../thirdparty/glm/glm/glm.hpp"
#include "../ThirdParty/glm/glm/gtc/type_ptr.hpp"
#include "../core/Component.h"
#include "../Core/GameObject.h"

class MeshRenderer : public Component
{
private:
	Camera* camera;
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
	glm::mat4 modelMatrix;
	GLuint vao, vbo, ebo, program, texture;
	glm::vec3 position, rotation, scale;

public:
	void calculateModelMatrix(); 
	MeshRenderer(GameObject* gameObject, Camera* _camera, MeshType meshType);
	~MeshRenderer();
	virtual void update() override;
	void setProgram(GLuint _program);
	void setTexture(GLuint texture);
	void setPosition(glm::vec3 _position);
	void setScale(glm::vec3 _scale);
	void setRotation(glm::vec3 _rotation);
};

