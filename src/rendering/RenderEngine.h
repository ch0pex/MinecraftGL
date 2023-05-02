#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Camera.h"
#include "MeshRenderer.h"
#include "../world/chunk/Chunklet.h"


class RenderEngine
{
private:
	Camera& camera; 
	GLFWwindow* window; 
	MeshRenderer solidRenderer;
	//MeshRenderer waterRenderer; 

public: 
	RenderEngine(Camera& _camera);
	~RenderEngine();

	void renderScene(); 
	bool shouldClose(); 

	void drawChunklet(Chunklet& chunklet); 
	GLFWwindow* getWindow();
	
};