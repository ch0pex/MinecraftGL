#pragma once
#include "GameState.h"
#include "../../world/World.h"
#include "../../player/Player.h"

class PlayingState : public GameState
{
public:
    void onEnter(Game& game) override;
    void onExit(Game& game) override;
    void update(Game& game) override;
    void handleInput(Player& player, GLFWwindow *window, u32 key, u32 action) override;
    void handleMouse(Player& player, GLFWwindow* window, f64 xpos, f64 ypos) override;
    
private:
    std::thread playerThread;
    std::mutex playerMutex;
};
