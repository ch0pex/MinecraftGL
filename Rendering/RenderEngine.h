#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>s
#include "../Util/Singleton.hpp"
#include "SolidRenderer.h"
#include "../Common/CommonHeaders.h"
#include "Camera.h"


class RenderEngine : public Singleton<RenderEngine>
{
private:
	GLFWwindow* window;

	SolidRenderer* solidRenderer; 
	// WaterRenderer waterRenderer; 
	// VegetationRenderer vegRenderer; 


	std::string readShader(const char* shaderPath);
	u32 createShader(GLenum shaderType, std::string source, const char* shaderName);

public:
	RenderEngine();
	~RenderEngine();
	u32 createProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	u32 getTextureID(const std::string TexturePath);
	GLFWwindow* getWindow();
	bool shouldClose();
	void renderScene(Camera &camera); 
	void drawChunklet(Chunklet& chunklet); 
};

