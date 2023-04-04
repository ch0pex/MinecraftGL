#include "GameEngine.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// Cuando una tecla es presionada, registra que tecla fue presionada
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}


GameEngine::GameEngine(): 
	camera(45.0f, 800, 600, 0.1f, 100.0f, glm::vec3(0.0f, 5.0f, 6.0f))
{
	glfwSetKeyCallback(renderEngine.getWindow(), key_callback);
	glfwSetCursorPosCallback(renderEngine.getWindow(), mouse_callback);

}

GameEngine::~GameEngine()
{

}


void GameEngine::loop(void)
{

    // El bucle principal de la aplicación
    while (!renderEngine.shouldClose())
    {
        // Lógica de la aplicación
    	renderEngine.renderScene(); 
        // Escucha los eventos de la ventana
        glfwPollEvents();
    }
    glfwTerminate();
    // Termina GLFW

}


