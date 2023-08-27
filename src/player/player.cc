#include "player.h"

Player::Player() :
    world_position_(glm::vec3(50.0f, 100.0f, 0.0f)),
    controls_enabled_(true),
    movement_speed_(100.0f),
    camera_(45.0f, 1920, 1080, .1f, 1000.0f, world_position_),
    currentState_(PlayerStateType::kGround)
{

}

void Player::Update() {

}

void Player::ChangeState(PlayerStateType state) {
  currentState_ = state;
}

PlayerStateType Player::GetState() {
  return currentState_;
}

void Player::Move(Direction dir, f32 speed_factor) {
  if (!controls_enabled_)
    return;

  switch (dir) {
    case Direction::kFront:
      world_position_ += camera_.front_ * speed_factor;
      break;
    case Direction::kBack:
      world_position_ -= camera_.front_ * speed_factor;
      break;
    case Direction::kRight:
      world_position_ += camera_.right_ * speed_factor;
      break;
    case Direction::kLeft:
      world_position_ -= camera_.right_ * speed_factor;
      break;
    case Direction::kUp:
      world_position_ += camera_.world_up_ * speed_factor;
      break;
    case Direction::kDown:
      world_position_ -= camera_.world_up_ * speed_factor;
      break;
  }
  camera_.SetPosition(world_position_);
}
void Player::LookAt(f64 xpos, f64 ypos) {
   if (!controls_enabled_)
     return;
   camera_.SetFront(xpos, ypos);
}
f32 Player::GetSpeed() const {
  return movement_speed_;
}

