#include "loading_state.h"
#include "game.h"

LoadingState::LoadingState(Game &game) : GameState(game) {}

void LoadingState::OnEnter() {
  game_.GetRenderEngine().SwapMouseMode(RenderEngine::MouseMode::kNormal);
  game_.Initialize();
}

void LoadingState::OnExit() {

}

void LoadingState::Update() {
  if(game_.GetWorld().IsLoaded())
    game_.SwitchState(GameStateType::kPlayingSpectator);
}

void LoadingState::HandleInput() {

}

void LoadingState::HandleMouse() {

}

void LoadingState::Render() {
  game_.GetRenderEngine().RenderLoadingScreen();
}

