#include "RenderEngine.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Thirdparty/stb-master/stb_image.h"


RenderEngine::RenderEngine()
{
	if (!glfwInit()) std::terminate();
	window = glfwCreateWindow(1920, 1080, "MineCraftGL", NULL, NULL);
	if (!window) {
		glfwTerminate();
		std::terminate();
		return; 
	}
	glfwMakeContextCurrent(window); 

	glewInit(); 

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

RenderEngine::~RenderEngine()
{

}

GLFWwindow* RenderEngine::getWindow()
{
	return window;
}

bool RenderEngine::shouldClose()
{
	return glfwWindowShouldClose(window);
}

GLuint RenderEngine::getTextureID(const std::string TexturePath)
{
	int width, height, channels;

	stbi_uc* image = stbi_load(TexturePath.c_str(), &width, &height, &channels, STBI_rgb);

	printf("TextureLoader: fileName %s \n", TexturePath.c_str());

	GLuint mtexture;

	//** load texture
	glGenTextures(1, &mtexture);
	glBindTexture(GL_TEXTURE_2D, mtexture);


	// Set texture wrapping 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);

	return mtexture;
}

void RenderEngine::renderScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4f, 5.0f, 0.75f, 1.0);


	
	//Meter aqui todas las meshes a renderizar



	glfwSwapBuffers(window);

}	


std::string RenderEngine::readShader(const char* shaderPath)
{
	std::string code;
	std::ifstream file(shaderPath, std::ios::in);

	if (!file.good()) {
		std::cout << "Error opening shader file" << std::endl;
		std::terminate();
	}
	file.seekg(0, std::ios::end);
	code.resize((unsigned int)file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&code[0], code.size());
	file.close();
	return code;
}

GLuint RenderEngine::createShader(GLenum shaderType, std::string source, const char* shaderName)
{
	int compile_result = 0;

	GLuint shader = glCreateShader(shaderType);

	const char* code_ptr = source.c_str();
	const int code_size = source.size();

	glShaderSource(shader, 1, &code_ptr, &code_size);
	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

	if (compile_result == GL_FALSE) {
		int info_length = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_length);
		std::vector<char> shader_log(info_length);
		glGetShaderInfoLog(shader, info_length, NULL, &shader_log[0]);
		std::cout << "Error compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl;
		return 0;
	}

	return shader;
}

GLuint RenderEngine::createProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
{
	int link_result = 0;

	std::string sourceVertexShader = readShader(vertexShaderPath);
	std::string sourceFragmentShader = readShader(fragmentShaderPath);

	GLuint vertexShader = createShader(GL_VERTEX_SHADER, sourceVertexShader, "VertexShader");
	GLuint fragmentShader = createShader(GL_FRAGMENT_SHADER, sourceFragmentShader, "FragmentShader");

	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glGetProgramiv(program, GL_LINK_STATUS, &link_result);

	if (link_result == GL_FALSE) {
		int info_length = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_length);
		std::vector<char> program_log(info_length);
		glGetProgramInfoLog(program, info_length, NULL, &program_log[0]);
		std::cout << "ERROR LINKING SHADERS." << std::endl << &program_log[0] << std::endl;
		return 0;
	}
	return program;
}
