#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glew.h>


#include "../common/public/common_headers.h"

class ShaderLoader {

private:
    static std::string ReadShader(std::string file_name);
    static u32 CreateShader(GLenum shader_type, std::string &source, const char *shader_name);
public:
    static u32 CreateProgram(const char *vertex_shader_name, const char *fragment_shader_name);

};