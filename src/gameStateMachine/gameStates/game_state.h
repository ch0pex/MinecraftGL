#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../common/public/common_headers.h"
#include "../../player/player.h"


struct Game;
enum class GameStateType {
    kStart,
    kLoading,
    kPlaying,
    kGameover,
};

class GameState {
public:
    virtual ~GameState() = default;
    virtual void OnEnter(Game &game) = 0;
    virtual void OnExit(Game &game) = 0;
    virtual void Update(Game &game) = 0;
    virtual void HandleInput(Player &player, GLFWwindow *window, u32 key, u32 action) = 0;
    virtual void HandleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) = 0;
};
