#include "Camera.h"
#include "../GameEngine.h"



Camera::Camera(GameEngine *_game, f32 _FOV, f32 _width, f32 _height, f32 _nearPlane, f32 _farPlane, glm::vec3 _position) :
	game(_game)
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
	yaw = 0; 
	pitch = 0; 


	std::cout << "Fov: " << FOV << std::endl; 
	std::cout << "Width: " << width << std::endl; 
	std::cout << "Height: " << height << std::endl; 
	std::cout << "Near Plane: " << nearPlane << std::endl; 
	std::cout << "Far Plane: " << farPlane << std::endl; 
	std::cout << "Position: " << position.x << ", " << position.y << ", " << position.z << std::endl; 

	projectionMatrix = glm::perspective(FOV, width / height, nearPlane, farPlane);
	calculateView();
}

Camera::~Camera()
{

}

void Camera::calculateView()
{

	viewMatrix = glm::lookAt(position, position + cameraFront, cameraUp); 
}

glm::mat4 Camera::getView()
{
	return viewMatrix; 
}

glm::mat4 Camera::getProjection()
{
	return projectionMatrix; 
}


glm::vec3 Camera::getPosition(){
	return position; 
}

void Camera::setPosition(glm::vec3 _position)
{
	position = _position; 
}



void Camera::update()
{
	while(game->isRunning()){
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
	calculateView();
	}


}


void Camera::move(Direction direction)
{
	movementDir = direction;
	//std::cout << position.x << ", " << position.y << ", " << position.z << "\n"; 
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
	calculateView();
}