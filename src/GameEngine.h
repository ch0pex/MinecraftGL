#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <Windows.h>
#include <iostream>
#include <ft2build.h>
#include FT_FREETYPE_H


#include "rendering/RenderEngine.h"
#include "rendering/Camera.h"
#include "world/World.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos); 

class GameEngine
{
private: 
	RenderEngine renderEngine; 
	Camera camera; 
	World world; 

public: 
	GameEngine();
	~GameEngine();
	void loop(); 

};