#include "playing_state.h"
#include "../../game_engine.h"
#include "../../player/player.h"

void PlayingState::OnEnter(Game &game) {
    player_thread_ = std::thread(&Player::Update, &game.player);
}

void PlayingState::OnExit(Game &game) {
    player_mutex_.lock();
    game.player.SetActive(false);
    player_mutex_.unlock();
    player_thread_.join();
}

void PlayingState::Update(Game &game) {
    game.world.Update(game.player.camera_);
    game.world.PrepareRender(game.render_engine, game.player.camera_);
    game.render_engine.RenderScene(game.player.camera_);

}

void PlayingState::HandleInput(Player &player, GLFWwindow *window, u32 key, u32 action) {
    player.camera_.Move(Camera::kStatic);
    // Cuando una tecla es presionada, registra que tecla fue presionada
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.camera_.Move(Camera::kFront);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.camera_.Move(Camera::kBack);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.camera_.Move(Camera::kLeft);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.camera_.Move(Camera::kRight);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        player.camera_.Move(Camera::kDown);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        player.camera_.Move(Camera::kUp);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void PlayingState::HandleMouse(Player &player, GLFWwindow *window, f64 xpos, f64 ypos) {
    player.camera_.MousePosToFront(xpos, ypos);
}
