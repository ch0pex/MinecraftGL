#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "game_state_machine/game_states.h"
#include "rendering/render_engine.h"
#include "player/player.h"
#include "world/world.h"
#include "input/input.h"

class Game {
public:
  Game();
  ~Game();
  void Loop();
  void SwitchState(GameStateType new_state);

  inline Player& GetPlayer() { return player_; }
  inline RenderEngine& GetRenderEngine() { return render_engine_; }
  inline World &GetWorld() { return world_; }
  inline InputInfo& GetInput() { return input_info_; }


private:
  RenderEngine render_engine_;
  InputInfo input_info_;
  Player player_;
  World world_;

  GameState* current_state_;
  std::unordered_map<GameStateType, GameState*> states_;
};
