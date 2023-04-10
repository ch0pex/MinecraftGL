#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>

#include "../common/public/CommonHeaders.h"
#include "../loaders/TextureLoader.h"
#include "../loaders/ShaderLoader.h"
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