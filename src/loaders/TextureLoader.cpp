#include "TextureLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <RootDir.h>
#include <iostream>


u32 TextureLoader::loadTexture(std::string fileName)
{
	int width, height, channels;

	std::cout << ROOT_DIR + fileName << std::endl; 
	stbi_uc* image = stbi_load((ROOT_DIR + fileName).c_str(), &width, &height, &channels, STBI_rgb);

	printf("TextureLoader: fileName %s \n", (ROOT_DIR + fileName).c_str());

	GLuint mtexture;

	//** load texture
	glGenTextures(1, &mtexture);
	glBindTexture(GL_TEXTURE_2D, mtexture);


	// Set texture wrapping 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// Set texture filtering parameters
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(image);


	return mtexture;
}