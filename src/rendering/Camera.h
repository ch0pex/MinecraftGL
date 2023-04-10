#pragma once 
#include <GL/glew.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "../common/public/CommonHeaders.h"

enum Direction {
	FRONT,
	BACK,
	RIGHT,
	LEFT,
	UP, 
	DOWN,
	STATIC
};
 

class Camera 
{
private:

	glm::mat4 viewMatrix, projectionMatrix; 
	glm::vec3 position, cameraFront, cameraUp; 



	f32 FOV;
	f32 width;
	f32 height;
	f32 nearPlane;
	f32 farPlane;

	bool firstMouse; 
	f64 lastX; 
	f64 lastY;
	f64 yaw;
	f64 pitch;

	Direction movementDir;
	f32 movementSpeed;
	void calculateView(); 

public:
	Camera(f32 _FOV, f32 _width, f32 _height, f32 _nearPlane, f32 _farPlane, glm::vec3 _position);
	~Camera();

	glm::mat4 getView();
	glm::mat4 getProjection(); 

	//void update(); 
	void lookAt(double xpos, double ypos); 

	void move(Direction direction);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);

	//float getSpeed(); 
	//void setSpeed(GLfloat speed);

	//void setDir(Direction dir); 

};

