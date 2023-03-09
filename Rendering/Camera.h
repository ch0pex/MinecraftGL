#pragma once
#include "../Thirdparty/glm/glm/glm.hpp"
#include "../Thirdparty/glm/glm/gtc/matrix_transform.hpp"
#include <GL/glew.h>


enum Direction {
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	UP, 
	DOWN
};
 

class Camera 
{
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;

	glm::vec3 position;
	glm::vec3 cameraFront; 
	glm::vec3 cameraUp; 


	GLfloat FOV;
	GLfloat width;
	GLfloat height;
	GLfloat nearPlane;
	GLfloat farPlane;

	bool firstMouse; 
	double lastX; 
	double lastY; 
	double yaw; 
	double pitch; 

	GLfloat movementSpeed;
	void calculateViewProjection(); 

public:
	Camera(GLfloat _FOV, GLfloat _width, GLfloat _height, GLfloat _nearPlane, GLfloat _farPlane, glm::vec3 _position);
	~Camera();

	glm::mat4 getView();
	glm::mat4 getProjection();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);

	float getSpeed(); 
	void setSpeed(GLfloat speed);

	void move(Direction direction); 
	void lookAt(double xpos, double ypos); 


};

