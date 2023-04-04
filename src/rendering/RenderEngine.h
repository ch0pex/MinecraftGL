#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>


class RenderEngine
{
private: 
	GLFWwindow* window; 

public: 
	RenderEngine();
	~RenderEngine();

	void renderScene(/*Camera*/); 
	bool shouldClose(); 

	GLFWwindow* getWindow();
	
};