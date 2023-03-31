#include "GameEngine.h"


Camera *GameEngine::camera = new Camera(45.0f, 1920, 1080, 0.1f, 100.0f, glm::vec3(0.0f, 5.0f, 6.0f));


GameEngine::GameEngine() 
{
	renderEngine = new RenderEngine(); 
	world = new World(*camera); 
	glfwSetKeyCallback(renderEngine->getWindow(), GameEngine::key_callback);
	glfwSetCursorPosCallback(renderEngine->getWindow(), GameEngine::mouse_callback);
}

GameEngine::~GameEngine()
{
	glfwTerminate();
}

void GameEngine::loop()
{
	while (!renderEngine->shouldClose())
	{
		camera->update();
		world->update(); 
		world->prepareRender(*renderEngine, *camera);
		renderEngine->renderScene(*camera);
		glfwPollEvents();
	}
}

void GameEngine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		GameEngine::camera->setDir(FRONT);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		GameEngine::camera->setDir(BACK);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		GameEngine::camera->setDir(LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		GameEngine::camera->setDir(RIGHT);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		GameEngine::camera->setDir(DOWN);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		GameEngine::camera->setDir(UP);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	


}

void GameEngine::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	GameEngine::camera->lookAt(xpos, ypos);
}
