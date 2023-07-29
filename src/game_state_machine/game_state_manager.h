#pragma once

#include <unordered_map>

#include "game_states/game_state.h"
#include "player/player.h"

struct Game;

class GameStateManager {
public:
  explicit GameStateManager(Game &game);
  ~GameStateManager();
  void Update() const;
  void Render() const;
  void HandleInput(InputInfo &input_info) const;
  void HandleMouse(InputInfo &input_info) const;
  void SwitchingState(GameStateType type);

private:
  Game &game_;
  GameState *current_state_;
  std::unordered_map<GameStateType, GameState *> states_;
};
