#include "game_state_manager.h"

#include "game_engine.h"
#include "game_states/loading_state.h"
#include "game_states/playing_state.h"
#include "game_states/game_over_state.h"


GameStateManager::GameStateManager(Game &game) : game_(game) {
  //states_[GameStateType::MENU] = new MenuState();
  states_[GameStateType::kLoading] = new LoadingState(game_);
  states_[GameStateType::kPlaying] = new PlayingState(game_);
  //states_[GameStateType::PAUSED] = new PausedState();
  states_[GameStateType::kGameOver] = new GameOverState(game_);
  //states_[GameStateType::EXIT] = new ExitState();
  current_state_ = states_[GameStateType::kPlaying];
  current_state_->OnEnter();
}

GameStateManager::~GameStateManager() {
  for (const auto state: states_)
    delete (state.second);

}

void GameStateManager::Update() const {
  current_state_->Update();
}

void GameStateManager::HandleInput(InputInfo &input_info) const {
  current_state_->HandleInput(input_info);
}

void GameStateManager::HandleMouse(InputInfo &input_info) const {
  current_state_->HandleMouse(input_info);
}

void GameStateManager::SwitchingState(GameStateType type) {
  current_state_->OnExit();
  current_state_ = states_[type];
  current_state_->OnEnter();
}
void GameStateManager::Render() const {
  current_state_->Render();
}

