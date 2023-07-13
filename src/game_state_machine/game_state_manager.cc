#include "game_state_manager.h"

#include "../game_engine.h"
#include "game_states/loading_state.h"
#include "game_states/playing_state.h"
#include "game_states/game_over_state.h"


GameStateManager::GameStateManager(Game &game) : game_(game) 
{
    //states_[GameStateType::MENU] = new MenuState();
    states_[GameStateType::kLoading] = new LoadingState();
    states_[GameStateType::kPlaying] = new PlayingState();
    //states_[GameStateType::PAUSED] = new PausedState();
    states_[GameStateType::kGameover] = new GameOverState();
    //states_[GameStateType::EXIT] = new ExitState();
    current_state_ = states_[GameStateType::kPlaying];
    current_state_->OnEnter(game);
}

GameStateManager::~GameStateManager()
{
    for(const auto state : states_)
        delete(state.second);

}

void GameStateManager::Update() const 
{
    current_state_->Update(game_);
}

void GameStateManager::HandleInput(GLFWwindow *window, u32 key, u32 action) const 
{
    current_state_->HandleInput(game_.player, window, key, action);
}

void GameStateManager::HandleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) const 
{
    current_state_->HandleMouse(player, window, xpos, ypos);
}

void GameStateManager::SwitchingState(GameStateType type) 
{
    current_state_->OnExit(game_);
    current_state_ = states_[type];
    current_state_->OnEnter(game_);
}

