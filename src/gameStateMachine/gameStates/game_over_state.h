#pragma once

#include "game_state.h"

class GameOverState : public GameState {
public:
    void OnEnter(Game &game) override;
    void OnExit(Game &game) override;
    void Update(Game &game) override;
    void HandleInput(Player &player, GLFWwindow *window, u32 key, u32 action) override;
    void HandleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) override;
};
