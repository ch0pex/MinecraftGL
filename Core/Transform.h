#pragma once
#include "Component.h"
#include "../ThirdParty/glm/glm/glm.hpp"


class Transform : public Component
{
private:
	glm::vec3 position, rotation, scale; 

public: 
	Transform(); 
	void setPosition(glm::vec3 _position); 
	void setRotation(glm::vec3 _rotation);
	void setScale(glm::vec3 _scale); 

	glm::vec3 getPosition(); 
	glm::vec3 getRotation(); 
	glm::vec3 getScale(); 
	virtual void update() override; 
};

