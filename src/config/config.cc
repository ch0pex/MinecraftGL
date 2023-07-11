#include "config.h"
#include <iostream>
#include <fstream>
#include "root_dir.h"

Config::Config()
{
    std::ifstream configJSON((ROOT_DIR + std::string("config.json")).c_str());
    Json config;
    if(configJSON.is_open())
    {
        configJSON >> config;
        chunk_distance = config["world"]["chunk_distance"];
        back_ground_color = glm::vec4(config["lighting"]["background_color"]["red"],
                                      config["lighting"]["background_color"]["green"],
                                      config["lighting"]["background_color"]["blue"],
                                      config["lighting"]["background_color"]["alpha"]);
        ambient_light_color = glm::vec3(config["lighting"]["ambient_light_color"]["red"],
                                      config["lighting"]["ambient_light_color"]["green"],
                                      config["lighting"]["ambient_light_color"]["blue"]);
        ambient_light_intensity = config["lighting"]["ambient_light_intensity"];

        sun_light_intensity = config["lighting"]["sun_light_intensity"];
	sun_light_color = glm::vec3(config["lighting"]["sun_light_color"]["red"],
				      config["lighting"]["sun_light_color"]["green"],
				      config["lighting"]["sun_light_color"]["blue"]);
	sun_light_direction = glm::vec3(config["lighting"]["sun_light_direction"]["x"],
				       config["lighting"]["sun_light_direction"]["y"],
				       config["lighting"]["sun_light_direction"]["z"]);

	solid_vertex_shader_path = config["shading"]["solid_vertex_shader_path"];
	solid_fragment_shader_path = config["shading"]["solid_fragment_shader_path"];
	water_vertex_shader_path = config["shading"]["water_vertex_shader_path"];
	water_fragment_shader_path = config["shading"]["water_fragment_shader_path"];
	texture_atlas_path = config["shading"]["texture_atlas_path"];
	configJSON.close();
    }
    else
    {
        std::cout << "Error en el archivo de configuracion, se usaron los valores por defecto\n";
        chunk_distance = kChunkSize;
        back_ground_color = glm::vec4(.0f,.0f,.0f,1.f);
        ambient_light_color = glm::vec3(.0f, .0f, .0f);
        ambient_light_intensity = .2f;
	sun_light_intensity = .4f;
	sun_light_color = glm::vec3(255.f, 255.f, 255.f);
	sun_light_direction = glm::vec3(300.f, 300.f, 300.f);
	solid_vertex_shader_path = "res/shaders/solidShader.vs";
	solid_fragment_shader_path = "res/shaders/solidShader.fs";
	water_vertex_shader_path = "res/shaders/waterShader.vs";
	solid_fragment_shader_path = "res/shaders/waterShader.fs";
	texture_atlas_path = "res/textures/stone.jpg";
    }
}

Config kGameConfig;
