#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <ft2build.h>

#include "gameStateMachine/game_state_manager.h"
#include "rendering/render_engine.h"
#include "player/player.h"
#include "world/world.h"

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