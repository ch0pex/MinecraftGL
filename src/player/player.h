#pragma once

#include <unordered_map>

#include "rendering/camera.h"
#include "player_states/player_state.h"
#include "math/vector_xz.h"


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

  f32 GetSpeed() const;
  glm::vec3 GetPos();

  void Move(Direction dir, f32 speed_factor);
  void LookAt(f64 xpos, f64 ypos);
  void Update();


  void SwitchState(PlayerStateType state);
  PlayerStateType GetState();

private:
  PlayerStateType currentState_;
  std::unordered_map<PlayerStateType, PlayerState *> states_;

  glm::vec3 world_position_;
  f32 movement_speed_;
public:
  Camera camera_;
};
