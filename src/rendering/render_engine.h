#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "mesh_renderer.h"
#include "../world/chunk/chunklet.h"


class RenderEngine
{
private: 
	GLFWwindow* window; 
	MeshRenderer solidRenderer;
	//MeshRenderer waterRenderer; 

public: 
	RenderEngine();
	~RenderEngine();

	void renderScene(Camera& camera); 
	bool shouldClose(); 

	void drawChunklet(Chunklet& chunklet); 
	GLFWwindow* getWindow();
	
};