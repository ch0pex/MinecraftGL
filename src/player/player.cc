#include "player.h"

Player::Player() :
    position_(glm::vec3(50.0f, 100.0f,0.0f)),
    controls_enabled_(true),
    movement_speed_(100.0f),
    camera_(45.0f, 1920, 1080, .1f, 1000.0f, position_),
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
      position_ += camera_.front_ * speed_factor;
      break;
    case Direction::kBack:
      position_ -= camera_.front_ * speed_factor;
      break;
    case Direction::kRight:
      position_ += camera_.right_ * speed_factor;
      break;
    case Direction::kLeft:
      position_ -= camera_.right_ * speed_factor;
      break;
    case Direction::kUp:
      position_ += camera_.world_up_ * speed_factor;
      break;
    case Direction::kDown:
      position_ -= camera_.world_up_ * speed_factor;
      break;
  }
  camera_.SetPosition(position_);
}
void Player::LookAt(f64 xpos, f64 ypos) {
   if (!controls_enabled_)
     return;
   camera_.SetFront(xpos, ypos);
}
f32 Player::GetSpeed() const {
  return movement_speed_;
}

