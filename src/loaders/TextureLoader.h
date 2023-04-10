#pragma once

#include "../common/public/CommonHeaders.h"
#include <GL/glew.h>

class TextureLoader {
public:
	static u32 loadTexture(std::string fileName); 
};