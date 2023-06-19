#include "playing_state.h"
#include "../../game_engine.h"
#include "../../player/player.h"

void PlayingState::onEnter(Game& game)
{
    playerThread = std::thread(&Player::update, &game.player);
}

void PlayingState::onExit(Game& game)
{
    playerMutex.lock();
    game.player.setActive(false);
    playerMutex.unlock();
    playerThread.join();    
}

void PlayingState::update(Game& game)
{
    game.world.update(game.player.camera); 
    game.world.prepareRender(game.renderEngine,game.player.camera);
    game.renderEngine.renderScene(game.player.camera); 
   
}

void PlayingState::handleInput(Player &player, GLFWwindow *window, u32 key, u32 action)
{
    player.camera.move(STATIC);
    // Cuando una tecla es presionada, registra que tecla fue presionada
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        player.camera.move(FRONT);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        player.camera.move(BACK);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        player.camera.move(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        player.camera.move(RIGHT);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        player.camera.move(DOWN);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        player.camera.move(UP);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void PlayingState::handleMouse(Player& player, GLFWwindow* window, f64 xpos, f64 ypos)
{
    player.camera.mousePosToFront(xpos, ypos);
}
