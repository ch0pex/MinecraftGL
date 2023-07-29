#pragma once

#include "rendering/camera.h"
#include "player_states/player_state.h"
#include <unordered_map>

enum class GameStateType;

class Player {
public:
  enum class Direction {
    kFront,
    kBack,
    kRight,
    kLeft,
    kUp,
    kDown,
  };
  Player();
  ~Player() = default;

  f32 GetSpeed();

  void Move(Direction dir, f32 speed_factor);
  void LookAt(f64 xpos, f64 ypos);
  void Update();

  void ChangeState(PlayerStateType state);
  PlayerStateType GetState();

private:
  PlayerStateType currentState_;
  std::unordered_map<PlayerStateType, PlayerState *> states_;

  glm::vec3 position_;
  bool controls_enabled_;
  f32 movement_speed_;
public:
  Camera camera_;
};
