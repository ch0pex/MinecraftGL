#pragma once

enum class PlayerStateType {
  kGround,
  kInactive,
  kInAir,
  kDead,
};

class PlayerState {
public:
  virtual ~PlayerState() = default;
  virtual void Update() = 0;
};
