#include "game_state_manager.h"

#include "../game_engine.h"
#include "gameStates/loading_state.h"
#include "gameStates/playing_state.h"
#include "gameStates/game_over_state.h"


GameStateManager::GameStateManager(Game &game) : game(game)
{
    //states[GameStateType::MENU] = new MenuState();
    states[GameStateType::LOADING] = new LoadingState();
    states[GameStateType::PLAYING] = new PlayingState();
    //states[GameStateType::PAUSED] = new PausedState();
    states[GameStateType::GAMEOVER] = new GameOverState();
    //states[GameStateType::EXIT] = new ExitState();
    currentState = states[GameStateType::PLAYING];
    currentState->onEnter(game);
}

GameStateManager::~GameStateManager()
{
    /*for(const auto state : states)
        delete(state.second);*/
    
}

void GameStateManager::update() const
{
    currentState->update(game);
}

void GameStateManager::handleInput(GLFWwindow* window, u32 key, u32 action) const
{
    currentState->handleInput(game.player, window, key, action);
}

void GameStateManager::handleMouse(Player& player, GLFWwindow* window, f64 xpos, f64 ypos) const
{
    currentState->handleMouse(player, window, xpos, ypos);
}

void GameStateManager::switchingState(GameStateType type)
{
    currentState->onExit(game);
    currentState = states[type];
    currentState->onEnter(game);
}

