#include "camera.h"
#include "../game_engine.h"



Camera::Camera(f32 _FOV, f32 _width, f32 _height, f32 _nearPlane, f32 _farPlane, glm::vec3 _position) 
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
	cameraRight = glm::normalize(glm::cross(cameraUp, cameraFront));
	firstMouse = true;
	yaw = 0; 
	pitch = 0; 
	projectionMatrix = glm::perspective(FOV, width / height, nearPlane, farPlane);
	calculateViewProj();
}

Camera::~Camera()
{

}

void Camera::calculateViewProj()
{
	viewMatrix = glm::lookAt(position, position + cameraFront, cameraUp);
	viewMatrix += glm::translate(viewMatrix, -position); 
	viewProjMatrix = projectionMatrix * viewMatrix;
}

glm::mat4 Camera::getView()
{
	return viewMatrix; 
}

glm::mat4 Camera::getProjection()
{
	return projectionMatrix; 
}

glm::vec3 Camera::getPosition()
{
	return position; 
}

void Camera::setPosition(glm::vec3 _position)
{
	position = _position; 
}

float* Camera::getViewProjValuePtr()
{
	return glm::value_ptr(viewProjMatrix); 
}

void Camera::update()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	switch (movementDir)
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
	calculateViewProj();
	frustum.update(viewProjMatrix);

	
}


void Camera::move(Direction direction)
{
	movementDir = direction;
}


void Camera::mousePosToFront(double xpos, double ypos)
{
	
	if (firstMouse)
	{

		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	double sensitivity = 0.1f;
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
	//cameraRight = glm::normalize(glm::cross(cameraFront, cameraUp));
	//cameraUp = glm::normalize(glm::cross(cameraRight, cameraFront));
	calculateViewProj();
	frustum.update(viewProjMatrix);
}

bool Camera::inFrustrum(Chunklet& chunklet)
{
	glm::vec3 chunkletCenter = chunklet.getPosition() + glm::vec3(8.f, 8.f, 8.f); 
	return frustum.isPointInside(chunkletCenter) || glm::distance(chunkletCenter, position) < 64.f;
}
