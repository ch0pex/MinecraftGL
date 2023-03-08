#include "Transform.h"

void Transform::setPosition(glm::vec3 _position)
{
	position = _position; 
}

void Transform::setRotation(glm::vec3 _rotation)
{
	rotation = _rotation; 
}

void Transform::setScale(glm::vec3 _scale)
{
	scale = _scale; 
	
}

glm::vec3 Transform::getPosition()
{
	return position; 
}

glm::vec3 Transform::getRotation()
{
	return rotation; 
}

glm::vec3 Transform::getScale()
{
	return scale; 
}

void Transform::update()
{

}

Transform::Transform() {
	position = glm::vec3(0.0f); 
	rotation = glm::vec3(0.0f);
	scale = glm::vec3(1.0f); 
}