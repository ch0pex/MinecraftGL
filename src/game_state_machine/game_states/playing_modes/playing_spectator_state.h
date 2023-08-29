#pragma once

#include "playing_state.h"

class PlayingSpectatorState : public PlayingState {
public:
  explicit PlayingSpectatorState(Game &game);
  void OnEnter() override;
  void Update() override;
  void HandleInput() override;
};

