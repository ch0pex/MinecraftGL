#include "playing_state.h"
#include "game.h"

PlayingState::PlayingState(Game &game) : GameState(game) {}

void PlayingState::OnEnter() {
  std::cout << "Enter to playing state\n";
  game_.GetRenderEngine().SwapMouseMode(RenderEngine::MouseMode::kDisabled);
}

void PlayingState::OnExit() {
  //save game
}

void PlayingState::Update() {
  game_.GetPlayer().Update();
  game_.GetWorld().Update(game_.GetPlayer().GetPos());
}

void PlayingState::Render() {
  game_.GetWorld().PrepareRender(game_.GetRenderEngine(), game_.GetPlayer().camera_);
  game_.GetRenderEngine().RenderScene(game_.GetPlayer().camera_);
}


void PlayingState::HandleMouse() {
  game_.GetPlayer().LookAt(game_.GetInput().mouse_pos->x, game_.GetInput().mouse_pos->y);
}
