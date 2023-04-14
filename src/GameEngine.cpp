#include "GameEngine.h"


Camera* cameraPointer;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    cameraPointer->move(STATIC);
	// Cuando una tecla es presionada, registra que tecla fue presionada
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPointer->move(FRONT);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPointer->move(BACK);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPointer->move(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPointer->move(RIGHT);
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cameraPointer->move(DOWN);
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        cameraPointer->move(UP);
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    cameraPointer->mousePosToFront(xpos, ypos); 
}


GameEngine::GameEngine(): 
	camera(45.0f, 1920, 1080, 0.1f, 100.0f, glm::vec3(0.0f, 60.0f, 6.0f)), 
    renderEngine()
{
    cameraPointer = &camera;
    
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
        camera.update();
        world.update(camera); 
        world.prepareRender(renderEngine,camera); 
    	renderEngine.renderScene(camera); 
        // Escucha los eventos de la ventana
        glfwPollEvents();
    }
    glfwTerminate();
    // Termina GLFW

}


