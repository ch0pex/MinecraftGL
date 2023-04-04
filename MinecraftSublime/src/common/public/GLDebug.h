#pragma once 

#include <GL/glew.h>
#include <iostream>

GLenum checkError_(const char* file, int line); 

#define glCheckError() checkError_(__FILE__, __LINE__) 