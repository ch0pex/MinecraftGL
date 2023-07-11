#pragma once

#include "game_state.h"
#include "../../world/world.h"
#include "../../player/player.h"

class PlayingState : public GameState {
public:
    void OnEnter(Game &game) override;
    void OnExit(Game &game) override;
    void Update(Game &game) override;
    void HandleInput(Player &player, GLFWwindow *window, u32 key, u32 action) override;
    void HandleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) override;

private:
    std::thread player_thread_;
};
