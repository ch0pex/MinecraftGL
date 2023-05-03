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


GameEngine::GameEngine() : 
    running(true),
	camera(this, 45.0f, 1920, 1080, 0.1f, 1000.0f, glm::vec3(0.0f, 75.0f, 6.0f)), 
    renderEngine(camera)
{
 
    cameraPointer = &camera;
    cameraThread = std::thread(&Camera::update, &camera); 
    
	glfwSetKeyCallback(renderEngine.getWindow(), key_callback);
	glfwSetCursorPosCallback(renderEngine.getWindow(), mouse_callback);
}


GameEngine::~GameEngine()
{
    cameraThread.join(); 
}


void GameEngine::loop(void)
{
    // El bucle principal de la aplicación
    while (!renderEngine.shouldClose())
    {
        world.update(camera); 
        world.prepareRender(renderEngine,camera); 
    	renderEngine.renderScene(); 
        glfwPollEvents(); // Escucha los eventos de la ventana
    }
    glfwTerminate();
    running = false; 
    // Termina GLFW
}

bool GameEngine::isRunning()
{
    return running; 
}
