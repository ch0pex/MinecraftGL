#include "Camera.h"
#include <iostream>


Camera::Camera(f32 _FOV, f32 _width, f32 _height, f32 _nearPlane, f32 _farPlane, glm::vec3 _position)
{
	FOV = _FOV; 
	width = _width; 
	height = _height;
	nearPlane = _nearPlane; 
	farPlane = _farPlane; 
	position = _position; 
	cameraFront = glm::vec3(0.0f, 0.0f, 0.0f); 
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); 

	std::cout << "Fov: " << FOV << std::endl; 
	std::cout << "Width: " << width << std::endl; 
	std::cout << "Height: " << height << std::endl; 
	std::cout << "Near Plane: " << nearPlane << std::endl; 
	std::cout << "Far Plane: " << farPlane << std::endl; 
	std::cout << "Position: " << position.x << ", " << position.y << ", " << position.z << std::endl; 



	calculateViewProjection();
}

Camera::~Camera()
{

}


void Camera::calculateViewProjection()
{
	viewProjectionMatrix = glm::perspective(FOV, width / height, nearPlane, farPlane) * glm::lookAt(position, position + cameraFront, cameraUp); 
}


glm::mat4 Camera::getViewProjection()
{
	return viewProjectionMatrix; 
}


glm::vec3 Camera::getPosition(){
	return position; 
}

void Camera::setPosition(glm::vec3 _position)
{
	position = _position; 
}
