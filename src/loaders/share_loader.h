#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <GL/glew.h>


#include "../common/public/common_headers.h"

class ShaderLoader {

private: 
	static std::string readShader(std::string fileName); 
	static u32 createShader(GLenum shaderType, std::string &source, const char* shaderName); 
public:
	static u32 createProgram(const char* vertexShaderName, const char* fragmentShaderName); 

};