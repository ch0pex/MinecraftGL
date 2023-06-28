#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <ft2build.h>

#include "game_state_machine/game_state_manager.h"
#include "rendering/render_engine.h"
#include "player/player.h"
#include "world/world.h"

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode);
void MouseCallback(GLFWwindow *window, double xpos, double ypos);

struct Game {
    RenderEngine render_engine;
    Player player;
    World world;
};

class GameEngine {
public:
    GameEngine();
    ~GameEngine();
    void Loop();

private:
    Game *game_;
    GameStateManager state_machine_;
};
