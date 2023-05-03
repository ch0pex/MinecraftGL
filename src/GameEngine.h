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

#include <thread> 

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

class GameEngine
{
private:
	bool running;
	Camera camera;
	RenderEngine renderEngine;
	World world;
	std::thread cameraThread;

public: 
	bool isRunning(); 
	GameEngine();
	~GameEngine();
	void loop(); 

};

void mouse_callback(GLFWwindow* window, double xpos, double ypos);