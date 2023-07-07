#include "game_engine.h"


GameStateManager *kStateMachinePointer;
Player *kPlayerPointer;

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) 
{
	kStateMachinePointer->HandleInput(window, key, action);
}

void MouseCallback(GLFWwindow *window, double xpos, double ypos) 
{
	kStateMachinePointer->HandleMouse(*kPlayerPointer, window, xpos, ypos);
}

GameEngine::GameEngine() :
        game_(new Game()),
        game_state_(*game_)
{
	kStateMachinePointer = &game_state_;
	kPlayerPointer = &game_->player;
	glfwSetKeyCallback(game_->render_engine.GetWindow(), KeyCallback);
	glfwSetCursorPosCallback(game_->render_engine.GetWindow(), MouseCallback);
}

GameEngine::~GameEngine() 
{
	std::cout << "GameEngine destructor called" << std::endl;
	delete (game_);
}

void GameEngine::Loop() 
{
	// El bucle principal de la aplicación
	while (!game_->render_engine.ShouldClose())
    {
		game_state_.Update();
		glfwPollEvents(); // Escucha los eventos de la ventana
	}
	glfwTerminate();

}

