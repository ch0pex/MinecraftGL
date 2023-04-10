#include "ShaderLoader.h"

#include <RootDir.h>

std::string ShaderLoader::readShader(std::string filename)
{
	std::string shaderCode; 
	std::ifstream file((ROOT_DIR + filename).c_str(), std::ios::in); 
	std::cout << "Shader check point\n"; 
	if (!file.good()) {
		std::cout << "Can't read file" << std::endl; 
		std::terminate(); 
	}

	file.seekg(0, std::ios::end); 
	shaderCode.resize((unsigned int) file.tellg()); 
	file.seekg(0, std::ios::beg); 
	file.read(&shaderCode[0], shaderCode.size()); 
	file.close(); 
	return shaderCode; 
}

GLuint ShaderLoader::createShader(GLenum shaderType, std::string& source, const char* shaderName)
/*Devuelve el shader creado o 0 en caso de que haya un error en su compilacion
Los pasos para ello son los siguientes: 
	- Se pasa el tipo de shader (Vertex shader, fragment shader, geomtry shader, tess controll shader y tess evaluation shader)
	- Se pasa como parametro el source code (escrito en GLSL o HLSL)
	- Se crea el shader (glCreateShader devuelve un identificador)
	- Se carga el codigo fuente en dicho shader
	- Se compila el shader
	- Se comprueba que el shader haya compilado correctamente.
	- Si el compile result ha sido falso. Muestras el info log con el error correspondiente. 
*/
{
	int compile_result = 0; 
	GLuint shader = glCreateShader(shaderType); 
	const char* shader_code_ptr = source.c_str(); 
	const int shader_code_size = source.size(); 
	glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size); 
	glCompileShader(shader); 
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result); 

	if (compile_result == GL_FALSE) {
		int info_log_length = 0; 
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length); 
		std::vector<char> shader_log(info_log_length); 
		glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
		std::cout << "Error compiling shader: " << shaderName << std::endl << &shader_log[0] << std::endl; 
		return 0; 
	}
	return shader; 
}

GLuint ShaderLoader::createProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
/* Devuelve el programa que se ejecutara en la GPU, este program shader, 
coordina los vertex shader y los fragment shader. Si hay un error devolvemos 0, en caso contrario
se devuelve el identificador del programa*/
{
	std::string source_vertex_shader = readShader(vertexShaderFilename); 
	std::string source_fragment_shader = readShader(fragmentShaderFilename); 

	GLuint vertex_shader = createShader(GL_VERTEX_SHADER, source_vertex_shader, "Vertex Shader"); 
	GLuint fragment_shader = createShader(GL_FRAGMENT_SHADER, source_fragment_shader, "Fragment Shader"); 

	int link_result = 0; 
	
	GLuint program = glCreateProgram(); 
	glAttachShader(program, vertex_shader); 
	glAttachShader(program, fragment_shader); 
	glLinkProgram(program); 
	glGetProgramiv(program, GL_LINK_STATUS, &link_result); 

	if (link_result == GL_FALSE) {
		int info_log_length = 0; 
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::vector<char> info_log(info_log_length); 
		glGetProgramInfoLog(program, info_log_length, NULL, &info_log[0]); 
		std::cout << "Shader Loader: LINK ERROR." << std::endl << &info_log[0] << std::endl; 
		return 0; 
	}
	return program; 
}