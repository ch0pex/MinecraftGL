#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game_state_machine/game_state_manager.h"
#include "rendering/render_engine.h"
#include "player/player.h"
#include "world/world.h"
#include "input/input.h"

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
  InputInfo input_info_;
  GameStateManager game_state_;
};
