#pragma once

#include <unordered_map>
#include "gameStates/game_state.h"
#include "../player/player.h"

struct Game;

class GameStateManager {
public:
    GameStateManager(Game &game);
    ~GameStateManager();
    void Update() const;
    void HandleInput(GLFWwindow *window, u32 key, u32 action) const;
    void HandleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) const;
    void SwitchingState(GameStateType type);

private:
    Game &game_;
    GameState *current_state_;
    std::unordered_map<GameStateType, GameState *> states_;
};
