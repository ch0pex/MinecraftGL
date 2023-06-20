#pragma once

#include <GL/glew.h>
#include <iostream>

GLenum CheckError(const char *file, int line);

#define GL_CHECK_ERROR() CheckError(__FILE__, __LINE__)