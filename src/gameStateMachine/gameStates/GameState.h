#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../common/public/CommonHeaders.h"
#include "../../player/Player.h"


struct Game;
enum class GameStateType {
    START,
    LOADING,
    PLAYING,
    GAMEOVER,
};

class GameState
{
public:
    virtual ~GameState() = default;
    virtual void onEnter(Game& game) = 0;
    virtual void onExit(Game& game) = 0;
    virtual void update(Game& game) = 0;
    virtual void handleInput(Player& player, GLFWwindow *window, u32 key, u32 action) = 0;
    virtual void handleMouse(Player& player, GLFWwindow *window, f64 xpos, f64 ypos) = 0;
};
