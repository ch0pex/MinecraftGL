#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/public/common_headers.h"
#include "player/player.h"
#include "input/input.h"


struct Game;
enum class GameStateType {
  kStart,
  kLoading,
  kPlaying,
  kGameOver,
};

class GameState {
public:
  explicit GameState(Game& game) : game_(game) {};
  virtual ~GameState() = default;
  virtual void OnEnter() = 0;
  virtual void OnExit() = 0;
  virtual void Update() = 0;
  virtual void Render() = 0;
  virtual void HandleInput(InputInfo &input_info) = 0;
  virtual void HandleMouse(InputInfo &input_info) = 0;
protected:
  Game& game_;
};
