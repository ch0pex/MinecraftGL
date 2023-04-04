#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>

#include "rendering/RenderEngine.h"
#include "rendering/Camera.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos); 

class GameEngine
{
private: 
	RenderEngine renderEngine; 
	Camera camera; 
public: 
	GameEngine();
	~GameEngine();
	void loop(); 

};