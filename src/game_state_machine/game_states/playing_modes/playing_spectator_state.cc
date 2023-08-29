#include "playing_spectator_state.h"
#include "game.h"

PlayingSpectatorState::PlayingSpectatorState(Game &game) : PlayingState(game) {}

void PlayingSpectatorState::OnEnter() {
  PlayingState::OnEnter();
  game_.GetPlayer().SwitchState(PlayerStateType::kInAir);
}

void PlayingSpectatorState::HandleInput() {
  f32 movement_speed = game_.GetPlayer().GetSpeed() * 4.0f;
  f32 factor = game_.GetInput().frame_time * movement_speed;

  if (game_.GetInput().PressedKeysAreDiag())
    factor *= 0.707f;

  // Keys for spectator mode movement
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
  if(game_.GetInput().keys[GLFW_KEY_L])
    game_.SwitchState(GameStateType::kLoading);
}
void PlayingSpectatorState::Update() {
  PlayingState::Update();
}
