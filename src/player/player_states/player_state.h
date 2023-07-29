#pragma once

enum class PlayerStateType {
  kGround,
  kAir,
  kDead,
};

class PlayerState {
public:
  virtual ~PlayerState() = default;
  virtual void Update() = 0;
};
