#include "shader_loader.h"
#include <root_dir.h>

std::string ShaderLoader::ReadShader(std::string file_name) {
    std::string shader_code;
    std::ifstream file((ROOT_DIR + file_name).c_str(), std::ios::in);
    if (!file.good()) {
        std::cout << "Can't read file" << std::endl;
        std::terminate();
    }

    file.seekg(0, std::ios::end);
    shader_code.resize((unsigned int) file.tellg());
    file.seekg(0, std::ios::beg);
    file.read(&shader_code[0], shader_code.size());
    file.close();
    return shader_code;
}

GLuint ShaderLoader::CreateShader(GLenum shader_type, std::string &source, const char *shader_name)
/*Devuelve el shader_ creado o 0 en caso de que haya un error en su compilacion
Los pasos para ello son los siguientes: 
	- Se pasa el tipo de shader_ (Vertex shader_, fragment shader_, geomtry shader_, tess controll shader_ y tess evaluation shader_)
	- Se pasa como parametro el source code (escrito en GLSL o HLSL)
	- Se crea el shader_ (glCreateShader devuelve un identificador)
	- Se carga el codigo fuente en dicho shader_
	- Se compila el shader_
	- Se comprueba que el shader_ haya compilado correctamente.
	- Si el compile result ha sido falso. Muestras el info log con el error correspondiente. 
*/
{
    int compile_result = 0;
    GLuint shader = glCreateShader(shader_type);
    const char *shader_code_ptr = source.c_str();
    const int shader_code_size = source.size();
    glShaderSource(shader, 1, &shader_code_ptr, &shader_code_size);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);

    if (compile_result == GL_FALSE) {
        int info_log_length = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
        std::vector<char> shader_log(info_log_length);
        glGetShaderInfoLog(shader, info_log_length, NULL, &shader_log[0]);
        std::cout << "Error compiling shader_: " << shader_name << std::endl << &shader_log[0] << std::endl;
        return 0;
    }
    return shader;
}

GLuint ShaderLoader::CreateProgram(const char *vertex_shader_name, const char *fragment_shader_name)
/* Devuelve el programa que se ejecutara en la GPU, este program shader_,
coordina los vertex shader_ y los fragment shader_. Si hay un error devolvemos 0, en caso contrario
se devuelve el identificador del programa*/
{
    std::string source_vertex_shader = ReadShader(vertex_shader_name);
    std::string source_fragment_shader = ReadShader(fragment_shader_name);

    GLuint vertex_shader = CreateShader(GL_VERTEX_SHADER, source_vertex_shader, "Vertex Shader");
    GLuint fragment_shader = CreateShader(GL_FRAGMENT_SHADER, source_fragment_shader, "Fragment Shader");

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
