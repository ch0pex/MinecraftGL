#pragma once

#include "game_state.h"

class GameOverState : public GameState {
public:
  explicit GameOverState(Game &game);
  void OnEnter() override;
  void OnExit() override;
  void Update() override;
  void Render() override;
  void HandleInput(InputInfo &input_info) override;
  void HandleMouse(InputInfo &input_info) override;
};
