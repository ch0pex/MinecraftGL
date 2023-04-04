#pragma once 
#include <GL/glew.h>
#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "common/public/CommonHeaders.h"

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

	glm::mat4 viewProjectionMatrix; 
	glm::vec3 position;
	glm::vec3 cameraFront; 
	glm::vec3 cameraUp; 


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
	void calculateViewProjection(); 

public:
	Camera(f32 _FOV, f32 _width, f32 _height, f32 _nearPlane, f32 _farPlane, glm::vec3 _position);
	~Camera();

	glm::mat4 getViewProjection();
	

	//void update(); 
	//void lookAt(f64 xpos, f64 ypos); 

	//void move(Direction dir);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 _position);

	//float getSpeed(); 
	//void setSpeed(GLfloat speed);

	//void setDir(Direction dir); 

};

