#pragma once

#include <string>
#include <vector>

#include "common/public/common_headers.h"

struct Config {
  Config();

  f32 max_framerate;

  u8 chunk_distance;
  u8 water_level;
  f32 water_opacity;

  glm::vec4 back_ground_color;
  glm::vec3 ambient_light_color;
  f32 ambient_light_intensity;

  glm::vec3 sun_light_direction;
  glm::vec3 sun_light_color;
  f32 sun_light_intensity;

  std::string texture_atlas_path;
  std::string solid_vertex_shader_path;
  std::string solid_fragment_shader_path;
  std::string water_vertex_shader_path;
  std::string water_fragment_shader_path;
  std::string sky_vertex_shader_path;
  std::string sky_fragment_shader_path;
  std::string skybox_faces_paths[2];
private:
  void SetConfigJson(Json &config);
  void SetDefaults();
};


extern Config kGameConfig;
