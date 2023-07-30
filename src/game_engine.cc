#include "game_engine.h"

#include "config/config.h"

bool kKeys[1024];
glm::vec2 kMousePos;

void KeyCallback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mode){
  if(key >= 0 && key <= 1024){
    if(action == GLFW_PRESS)
      kKeys[key] = true;
    else if(action == GLFW_RELEASE)
      kKeys[key] = false;
  }
}

void MouseCallback(GLFWwindow *window, f64 xpos, f64 ypos){
  kMousePos.x = xpos;
  kMousePos.y = ypos;
}

GameEngine::GameEngine() :
    game_(new Game()),
    game_state_(*game_),
    input_info_ {kKeys, &kMousePos, 0.0f}
{
  glfwSetKeyCallback(game_->render_engine.GetWindow(), KeyCallback);
  glfwSetCursorPosCallback(game_->render_engine.GetWindow(), MouseCallback);
}

GameEngine::~GameEngine() {
  std::cout << "GameEngine destructor called" << std::endl;
  delete (game_);
}

void GameEngine::Loop() {
  const f32 dt = 1.0f / 175.0f;
  std::chrono::microseconds current_time;
  std::chrono::microseconds new_time;
  f32 t = 0.0f, accumulator = 0.0f;

  current_time = Time::Now();
  while (!game_->render_engine.ShouldClose()) {
    new_time = Time::Now();
    input_info_.frame_time = (new_time.count() - current_time.count()) / 1000000.0f;
    //Time::SetLastFrameTime(frame_time);
    current_time = new_time;
    accumulator += input_info_.frame_time;

    game_state_.HandleInput(input_info_);
    game_state_.HandleMouse(input_info_);

    glfwPollEvents();
    while (accumulator >= dt) {
      game_state_.Update();

      accumulator -= dt;
      t += dt;
    }
    game_state_.Render();
  }
  glfwTerminate();
}


