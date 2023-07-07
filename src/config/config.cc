#include "config.h"
#include <iostream>
#include <fstream>
#include "root_dir.h"

Config::Config()
{
    std::ifstream configJSON((ROOT_DIR + std::string("config.json")).c_str());
    Json config;
    std::string file;
    if(configJSON.is_open())
    {
        configJSON >> config;
        chunk_distance = config["world"]["chunk_distance"];
        back_ground_color = glm::vec4(config["rendering"]["background_color"]["red"],
                                      config["rendering"]["background_color"]["green"],
                                      config["rendering"]["background_color"]["blue"],
                                      config["rendering"]["background_color"]["alpha"]);
        global_light_color= glm::vec3(config["rendering"]["global_light_color"]["red"],
                                      config["rendering"]["global_light_color"]["green"],
                                      config["rendering"]["global_light_color"]["blue"]);
        global_light_intensity = config["rendering"]["global_light_intensity"];
    }
    else
    {
        std::cout << "Error en el archivo de configuracion, se usaron los valores por defecto\n";
        chunk_distance = kChunkSize;
        back_ground_color = glm::vec4(.0f,.0f,.0f,1.f);
        global_light_color = glm::vec3(.0f, .0f, .0f);
        global_light_intensity = .2f;
    }
}

Config kGameConfig;
