#pragma once
#include "../common/public/common_headers.h"

struct Config {
    u32 chunk_distance;
    glm::vec4 back_ground_color;
    glm::vec3 global_light_color;
    f32 global_light_intensity;
    u8 water_level;
    Config();
};

extern Config kGameConfig;
