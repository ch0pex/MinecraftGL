#include "playing_state.h"

#include "game.h"

PlayingState::PlayingState(Game &game) : GameState(game) {}

void PlayingState::OnEnter() {

}

void PlayingState::OnExit() {

}

void PlayingState::Update() {
  game_.GetPlayer().Update();
  game_.GetWorld().Update(game_.GetPlayer().GetPos());
}

void PlayingState::Render() {
  game_.GetWorld().PrepareRender(game_.GetRenderEngine(), game_.GetPlayer().camera_);
  game_.GetRenderEngine().RenderScene(game_.GetPlayer().camera_);
}

void PlayingState::HandleInput() {
  f32 movement_speed = game_.GetPlayer().GetSpeed();
  f32 factor = game_.GetInput().frame_time * movement_speed;

  if (game_.GetInput().PressedKeysAreDiag())
    factor *= 0.707f;

  // Keys for GetPlayer() movement
  if (game_.GetInput().keys[GLFW_KEY_W])
    game_.GetPlayer().Move(Player::Direction::kFront, factor);
  if (game_.GetInput().keys[GLFW_KEY_S])
    game_.GetPlayer().Move(Player::Direction::kBack, factor);
  if (game_.GetInput().keys[GLFW_KEY_A])
    game_.GetPlayer().Move(Player::Direction::kLeft, factor);
  if (game_.GetInput().keys[GLFW_KEY_D])
    game_.GetPlayer().Move(Player::Direction::kRight, factor);
  if (game_.GetInput().keys[GLFW_KEY_Q])
    game_.GetPlayer().Move(Player::Direction::kDown, factor);
  if (game_.GetInput().keys[GLFW_KEY_E])
    game_.GetPlayer().Move(Player::Direction::kUp, factor);
  if (game_.GetInput().keys[GLFW_KEY_ESCAPE])
    glfwSetWindowShouldClose(game_.GetRenderEngine().GetWindow(), true);
}

void PlayingState::HandleMouse() {
  game_.GetPlayer().LookAt(game_.GetInput().mouse_pos->x, game_.GetInput().mouse_pos->y);
}
