
#include "RenderEngine.h"





RenderEngine::RenderEngine() 
{
	if (!glfwInit())
	{
		// Manejo de error
		std::terminate();
	}

	// Crea una ventana de GLFW
	window = glfwCreateWindow(1920, 1080, "CraftGL", NULL, NULL);

	if (!window)
	{
		// Manejo de error
		glfwTerminate();
		std::terminate();
	}

	// Hace que la ventana sea el contexto actual
	glfwMakeContextCurrent(window);

	// Inicializa GLEW
	if (glewInit() != GLEW_OK)
	{
		// Manejo de error
		glfwTerminate();
		std::terminate();
	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);


	u32 shader = ShaderLoader::createProgram("res/shaders/solidShader.vs", "res/shaders/solidShader.fs"); 
	u32 texture = TextureLoader::loadTexture("res/textures/stone.jpg"); 

	solidRenderer.setTexture(texture);
	solidRenderer.setShader(shader);
	solidRenderer.addReferenceMesh(); 
	std::cout << "Shader: " << shader << "\n"; 
	std::cout << "Texture: " << texture << "\n"; 
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

RenderEngine::~RenderEngine()
{
	
}


void RenderEngine::renderScene(Camera& camera)
{
    	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4f, 5.0f, 0.75f, 1.0);

		solidRenderer.render(camera); 
	

        glfwSwapBuffers(window);

}

void RenderEngine::drawChunklet(Chunklet& chunklet)
{
	if (chunklet.getFaces()) solidRenderer.addMesh(chunklet.mesh); 
}



bool RenderEngine::shouldClose()
{
	return glfwWindowShouldClose(window);
}


GLFWwindow* RenderEngine::getWindow()
{
	return window; 
}


