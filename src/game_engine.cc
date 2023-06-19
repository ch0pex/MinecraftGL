#include "game_engine.h"


GameStateManager *stateMachinePointer;
Player *playerPointer;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    stateMachinePointer->handleInput(window, key, action);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    stateMachinePointer->handleMouse(*playerPointer, window, xpos, ypos);
}

GameEngine::GameEngine() :
    game(new Game()),
    stateMachine(*game)
{
    stateMachinePointer = &stateMachine;
    playerPointer = &game->player;
    glfwSetKeyCallback(game->renderEngine.getWindow(), key_callback);
    glfwSetCursorPosCallback(game->renderEngine.getWindow(), mouse_callback);
}

GameEngine::~GameEngine()
{
    std::cout << "GameEngine destructor called" << std::endl;
    delete (game);
}

void GameEngine::loop()
{

    // El bucle principal de la aplicación
    while (!game->renderEngine.shouldClose())
    {
        stateMachine.update();
        /*world.update(camera); 
        world.prepareRender(renderEngine,camera); */
        //game->renderEngine.renderScene(game->player.camera);
        glfwPollEvents(); // Escucha los eventos de la ventana
    }
    glfwTerminate();

}

