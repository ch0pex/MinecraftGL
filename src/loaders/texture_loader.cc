#include "texture_loader.h"

#define STB_IMAGE_IMPLEMENTATION

#include <stb_image.h>
#include <root_dir.h>
#include <iostream>


u32 TextureLoader::LoadTexture(const std::string &file_name) {
  s32 width, height, channels;
  u32 mtexture;

  std::cout << ROOT_DIR + file_name << std::endl;
  stbi_uc *image = stbi_load((ROOT_DIR + file_name).c_str(), &width, &height, &channels, STBI_rgb);

  printf("TextureLoader: file_name %s \n", (ROOT_DIR + file_name).c_str());

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


u32 TextureLoader::LoadSkyTexture(const std::string faces[2]) {
  s32 width, height, channels;
  u32 mtexture;

  glGenTextures(1, &mtexture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, mtexture);

  stbi_uc *bot_top_image = stbi_load((ROOT_DIR + faces[0]).c_str(), &width, &height, &channels, 0);
  stbi_uc *sides_image = stbi_load((ROOT_DIR + faces[1]).c_str(), &width, &height, &channels, 0);

  if (bot_top_image && sides_image) {
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 0, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 sides_image);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 1, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 sides_image);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 2, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 bot_top_image);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 3, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 bot_top_image);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 4, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 sides_image);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + 5, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE,
                 sides_image);
    stbi_image_free(bot_top_image);
    stbi_image_free(sides_image);
  } else {
    std::cout << "Error loading skybox" << std::endl;
    stbi_image_free(bot_top_image);
    stbi_image_free(sides_image);
  }

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return mtexture;
};