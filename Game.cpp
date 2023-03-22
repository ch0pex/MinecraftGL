#include "Game.h"


Camera Game::camera = Camera(45.0f, 1920, 1080, 0.1f, 100.0f, glm::vec3(5.0f, 0.0f, 0.0f)); 


Game::Game() 
{
	renderEngine = new RenderEngine(); 
	world = new World(camera); 
	glfwSetKeyCallback(renderEngine->getWindow(), Game::key_callback);
	glfwSetCursorPosCallback(renderEngine->getWindow(), Game::mouse_callback);
}

Game::~Game()
{
	glfwTerminate();
}

void Game::loop()
{
	while (!renderEngine->shouldClose())
	{
		world->update(); 
		world->prepareRender(*renderEngine, camera);
		renderEngine->renderScene(camera);
		glfwPollEvents();
	}
}

void Game::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(FRONT);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		Game::camera.move(BACK);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		Game::camera.move(LEFT);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		Game::camera.move(RIGHT);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		Game::camera.move(DOWN);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		Game::camera.move(UP);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Game::camera.lookAt(xpos, ypos);
}
