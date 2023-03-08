#include "Camera.h"


Camera::Camera(GLfloat _FOV, GLfloat _width, GLfloat _height, GLfloat _nearPlane, GLfloat _farPlane, glm::vec3 _position)
{
	FOV = _FOV; 
	width = _width; 
	height = _height; 
	nearPlane = _nearPlane; 
	farPlane = _farPlane; 
	position = _position;
	movementSpeed = 0.5f; 
	cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	
	calculateViewProjection(); 
}

Camera::~Camera()
{

}

void Camera::calculateViewProjection()
{
	viewMatrix = glm::lookAt(position, position + cameraFront, cameraUp);
	projectionMatrix = glm::perspective(FOV, width / height, nearPlane, farPlane);
}

glm::mat4 Camera::getView()
{
	return viewMatrix;
}

glm::mat4 Camera::getProjection()
{
	return	projectionMatrix;
}

glm::vec3 Camera::getPosition()
{
	return	position;
}

void Camera::setPosition(glm::vec3 _position)
{
	position = _position;
}

float Camera::getSpeed()
{
	return movementSpeed;
}

void Camera::setSpeed(GLfloat speed)
{
	if (speed > 0 && speed < 0.5f) 
		movementSpeed = speed; 
}

void Camera::move(Direction direction)
{
	switch (direction)
	{
	case FRONT:
		position += movementSpeed * cameraFront;
		break;
	case BACK:
		position -= movementSpeed * cameraFront;
		break;
	case RIGHT:
		position += glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed;
		break;
	case LEFT:
		position -= glm::normalize(glm::cross(cameraFront, cameraUp)) * movementSpeed;
		break;
	case UP:
		position += movementSpeed * cameraUp;
		break;
	case DOWN:
		position -= movementSpeed * cameraUp;
		break;
	default:
		break;
	}
	calculateViewProjection();
}

void Camera::lookAt(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 direction;
	direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(direction);
	calculateViewProjection(); 
}

