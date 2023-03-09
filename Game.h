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
	World world; 
	RenderEngine renderEngine; // Pass as arguemnt render config

public: 
	static Camera* camera;
	Game(); 
	~Game();
	void loop(); 

};

