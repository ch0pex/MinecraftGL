#pragma once

#include "playing_state.h"

class PlayingSurvivalState : public PlayingState {
public:
  explicit PlayingSurvivalState(Game &game);
  void OnEnter() override;
  void Update() override;
  void HandleInput() override;
};

