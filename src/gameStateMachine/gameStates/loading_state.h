#pragma once
#include "game_state.h"

class LoadingState : public GameState
{
public:
    void onEnter(Game& game) override;
    void onExit(Game& game) override;
    void update(Game& game) override;
    void handleInput(Player& player, GLFWwindow* window, u32 key, u32 action) override;
    void handleMouse(Player& player, GLFWwindow* window, f64 xpos, f64 ypos) override;
};
