#pragma once

#include "game_state.h"

class LoadingState : public GameState {
public:
  explicit LoadingState(Game &game);
  void OnEnter() override;
  void OnExit() override;
  void Update() override;
  void Render() override;
  void HandleInput() override;
  void HandleMouse() override;
};
