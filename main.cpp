#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Core/GameEngine.h"
#include "Rendering/RenderEngine.h"
#include "Core/Block.h"
#include <Windows.h>
#include <iostream>
#include <thread>


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow* window, double xpos, double ypos); 
Camera* camera = new Camera(45.0f, 1920, 1080, 0.1f, 100.0f, glm::vec3(0.0f, 5.0f, 6.0f));

int main() {

	GameEngine* gameEngine = new GameEngine(); // Pass as argument game config 
	RenderEngine* renderEngine = new RenderEngine(); // Pass as arguemnt render config

	GLuint blockProgram = renderEngine->createProgram("Assets/Shaders/TextureModel.vs", "Assets/Shaders/TextureModel.fs"); 
	GLuint stoneTexture = renderEngine->getTextureID("Assets/Textures/Blocks/Stone.jpg"); 
	Block* myCube = new Block(camera, stoneTexture, blockProgram);

	gameEngine->addGameObject(myCube); 

	glfwSetInputMode(renderEngine->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetKeyCallback(renderEngine->getWindow(), key_callback); 
	glfwSetCursorPosCallback(renderEngine->getWindow(), mouse_callback);

	while (!renderEngine->shouldClose()) 
	{
		std::cout << camera->getPosition().x << ", " << camera->getPosition().y << ", " << camera->getPosition().z << std::endl;
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4f, 5.0f, 0.75f, 1.0);
		for (GameObject* gameObject : *gameEngine->getGameObjects()) {
			gameObject->update();
		}
		glfwSwapBuffers(renderEngine->getWindow());
		glfwPollEvents();
	
	}
		

	glfwTerminate();
	delete(gameEngine); 
	delete(renderEngine); 
	delete(camera); 
	
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->move(FRONT); 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->move(BACK);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->move(LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->move(RIGHT);
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		camera->move(DOWN);
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		camera->move(UP);
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	camera->lookAt(xpos, ypos); 
}
