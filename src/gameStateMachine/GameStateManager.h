#pragma once

#include <unordered_map>
#include "gameStates/GameState.h"
#include "../player/Player.h"

struct Game;

class GameStateManager
{
public:
    GameStateManager(Game &game);
    ~GameStateManager();
    void update() const;
    void handleInput(GLFWwindow *window, u32 key, u32 action) const;
    void handleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) const;
    void switchingState(GameStateType type);
    
private:
    Game &game;
    GameState *currentState;
    std::unordered_map<GameStateType, GameState*> states;
};
