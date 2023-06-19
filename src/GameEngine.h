#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <ft2build.h>

#include "gameStateMachine/GameStateManager.h"
#include "rendering/RenderEngine.h"
#include "player/Player.h"
#include "world/World.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

struct Game {
	RenderEngine renderEngine;
	Player player;
	World world;
};

class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void loop();
	
private:
	Game *game;
	GameStateManager stateMachine;
};