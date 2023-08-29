#pragma once

#include "game_state_machine/game_states/game_state.h"

class PlayingState : public GameState {
public:
  explicit PlayingState(Game &game);
  void OnEnter() override;
  void OnExit() override;
  void Update() override;
  void Render() override;
  void HandleMouse() override;
};
