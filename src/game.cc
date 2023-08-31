#include "game.h"

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

Game::Game() :
        input_info_ {kKeys, &kMousePos, 0.0f}
{
  //states_[GameStateType::MENU] = new MenuState();
  states_[GameStateType::kLoading] = new LoadingState(*this);
  states_[GameStateType::kPlayingSpectator] = new PlayingSpectatorState(*this);
  states_[GameStateType::kPlayingSurvival] = new PlayingSurvivalState(*this);
  //states_[GameStateType::PAUSED] = new PausedState();
  states_[GameStateType::kGameOver] = new GameOverState(*this);
  //states_[GameStateType::EXIT] = new ExitState();
  current_state_ = states_[GameStateType::kLoading];
  glfwSetKeyCallback(render_engine_.GetWindow(), KeyCallback);
  glfwSetCursorPosCallback(render_engine_.GetWindow(), MouseCallback);

  current_state_->OnEnter();
}

Game::~Game() {
  for(auto& state : states_)
    delete(state.second);
  std::cout << "Game destructor called" << std::endl;
}

void Game::Initialize() {
  player_.reset();
  world_.reset();
  player_.emplace();
  world_.emplace(player_.value());
}

void Game::Loop() {
  const f32 dt = 1.0f / 175.0f;
  std::chrono::microseconds current_time;
  std::chrono::microseconds new_time;
  f32 t = 0.0f, accumulator = 0.0f;

  current_time = Time::Now();
  while (!render_engine_.ShouldClose()) {
    new_time = Time::Now();
    input_info_.frame_time = (new_time.count() - current_time.count()) / 1000000.0f;
    //Time::SetLastFrameTime(frame_time);
    current_time = new_time;
    accumulator += input_info_.frame_time;

    current_state_->HandleInput();
    current_state_->HandleMouse();

    glfwPollEvents();
    while (accumulator >= dt) {
      current_state_->Update();
      accumulator -= dt;
      t += dt;
    }
    current_state_->Render();
  }
  RenderEngine::Terminate();
}


void Game::SwitchState(GameStateType next_state){
    current_state_->OnExit();
    current_state_ = states_[next_state];
    current_state_->OnEnter();
}
