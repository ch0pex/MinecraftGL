#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <optional>

#include "game_state_machine/game_states.h"
#include "rendering/render_engine.h"
#include "player/player.h"
#include "world/world.h"
#include "input/input.h"

class Game {
public:
  Game();
  ~Game();

  void Initialize();
  void Loop();
  void SwitchState(GameStateType new_state);

  inline RenderEngine& GetRenderEngine() { return render_engine_; }
  inline Player& GetPlayer() { return player_.value(); }
  inline World& GetWorld() { return world_.value(); }
  inline InputInfo& GetInput() { return input_info_; }


private:
  RenderEngine render_engine_;
  std::optional<Player> player_;
  std::optional<World> world_;
  InputInfo input_info_;

  GameState* current_state_;
  std::unordered_map<GameStateType, GameState*> states_;
};
