#include "texture_loader.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <root_dir.h>
#include <iostream>


u32 TextureLoader::LoadTexture(const std::string& file_name) {
    int width, height, channels;

    std::cout << ROOT_DIR + file_name << std::endl;
    stbi_uc *image = stbi_load((ROOT_DIR + file_name).c_str(), &width, &height, &channels, STBI_rgb);

    printf("TextureLoader: file_name %s \n", (ROOT_DIR + file_name).c_str());

    GLuint mtexture;

    //** load texture_
    glGenTextures(1, &mtexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mtexture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    return mtexture;
}
