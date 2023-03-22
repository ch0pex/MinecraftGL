#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Rendering/RenderEngine.h"
#include "Rendering/Camera.h"
#include "Core/World.h"
#include <Windows.h>
#include <iostream>
#include <thread>

class Game
{
private: 
	static Camera camera;
	
	World* world; 
	RenderEngine* renderEngine; // Pass as arguemnt render config

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

public: 
	Game(); 
	~Game();
	void loop(); 

};

