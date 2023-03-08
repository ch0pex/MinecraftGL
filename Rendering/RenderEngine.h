#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "../Util/Singleton.hpp"
#include "../Core/GameEngine.h"




class RenderEngine : public Singleton<RenderEngine>
{
private:

	GLFWwindow* window;
	std::string readShader(const char* shaderPath);
	GLuint createShader(GLenum shaderType, std::string source, const char* shaderName);

public:
	RenderEngine();
	~RenderEngine();
	GLuint createProgram(const char* vertexShaderPath, const char* fragmentShaderPath);
	GLuint getTextureID(const std::string TexturePath);
	void renderScene(); 
	GLFWwindow* getWindow();
	bool shouldClose();
};

