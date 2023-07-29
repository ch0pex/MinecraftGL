#include "playing_state.h"

#include "game_engine.h"

PlayingState::PlayingState(Game &game) : GameState(game) {}

void PlayingState::OnEnter() {

}

void PlayingState::OnExit() {

}

void PlayingState::Update() {
  game_.player.Update();
  game_.world.Update(game_.player.camera_);
}

void PlayingState::Render() {
  game_.world.PrepareRender(game_.render_engine, game_.player.camera_);
  game_.render_engine.RenderScene(game_.player.camera_);
}

void PlayingState::HandleInput(InputInfo &input_info) {
  f32 movement_speed = game_.player.GetSpeed();
  f32 factor = input_info.frame_time * movement_speed;

  if (input_info.PressedKeysAreDiag())
    factor *= 0.707f;

  // Keys for player movement
  if (input_info.keys[GLFW_KEY_W])
    game_.player.Move(Player::Direction::kFront, factor);
  if (input_info.keys[GLFW_KEY_S])
    game_.player.Move(Player::Direction::kBack, factor);
  if (input_info.keys[GLFW_KEY_A])
    game_.player.Move(Player::Direction::kLeft, factor);
  if (input_info.keys[GLFW_KEY_D])
    game_.player.Move(Player::Direction::kRight, factor);
  if (input_info.keys[GLFW_KEY_Q])
    game_.player.Move(Player::Direction::kDown, factor);
  if (input_info.keys[GLFW_KEY_E])
    game_.player.Move(Player::Direction::kUp, factor);
  if (input_info.keys[GLFW_KEY_ESCAPE])
    glfwSetWindowShouldClose(game_.render_engine.GetWindow(), true);
}

void PlayingState::HandleMouse(InputInfo &input_info) {
  game_.player.LookAt(input_info.mouse_pos->x, input_info.mouse_pos->y);
}
