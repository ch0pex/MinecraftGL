#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>

#include "Camera.h"
#include "SolidRenderer.h"


class RenderEngine
{
private: 
	GLFWwindow* window; 
	SolidRenderer solidRenderer;

public: 
	RenderEngine();
	~RenderEngine();

	void renderScene(Camera& camera); 
	bool shouldClose(); 

	GLFWwindow* getWindow();
	
};