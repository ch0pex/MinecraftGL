#include "config.h"
#include <iostream>
#include <fstream>
#include "root_dir.h"

Config::Config()
{
    std::ifstream configJSON((ROOT_DIR + std::string("config.json")).c_str());
    Json config;

    if (configJSON.is_open())
    {
        configJSON >> config;
        try
        {
            SetConfigJSON(config);
            configJSON.close();
        }
        catch(const std::exception& e)
        {
            std::cout << "Error en el archivo de configuracion, se usaron los valores por defecto\n";
            SetDefaults();
        }
    }
    else
    {
        std::cout << "Error en el archivo de configuracion, se usaron los valores por defecto\n";
        SetDefaults();
    } 
}

void Config::SetDefaults()
{

    //----------------------------------World---------------------------- 
    chunk_distance = kChunkSize;
    water_level = 60;
    water_opacity = 0.5f;

    //------------------------------Lighting----------------------------
    back_ground_color = glm::vec4(.0f, .0f, .0f, 1.f);
    ambient_light_color = glm::vec3(.0f, .0f, .0f);
    ambient_light_intensity = .2f;
    sun_light_intensity = .4f;
    sun_light_color = glm::vec3(255.f, 255.f, 255.f);
    sun_light_direction = glm::vec3(300.f, 300.f, 300.f);

    // -----------------------------Shading------------------------------
    solid_vertex_shader_path = "res/shaders/solidShader.vs";
    solid_fragment_shader_path = "res/shaders/solidShader.fs";
    water_vertex_shader_path = "res/shaders/solidShader.vs";
    water_fragment_shader_path = "res/shaders/waterShader.fs";
    sky_vertex_shader_path = "res/shaders/skyShader.vs";
    sky_fragment_shader_path = "res/shaders/skyShader.fs";
    texture_atlas_path = "res/textures/stone.jpg";
    skybox_faces_paths[0] = "res/textures/skybox/bot_top.png";
    skybox_faces_paths[1] = "res/textures/skybox/sides.png";
}

void Config::SetConfigJSON(Json &config)
{
    //----------------------------------World---------------------------- 
    chunk_distance = config["world"]["chunk_distance"];
    water_level = config["world"]["water_level"];
    water_opacity = config["world"]["water_opacity"];

    //------------------------------Lighting----------------------------
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

    // -----------------------------Shading------------------------------
    solid_vertex_shader_path = config["shading"]["solid_vertex_shader_path"];
    solid_fragment_shader_path = config["shading"]["solid_fragment_shader_path"];
    water_vertex_shader_path = config["shading"]["water_vertex_shader_path"];
    water_fragment_shader_path = config["shading"]["water_fragment_shader_path"];
    sky_fragment_shader_path = config["shading"]["sky_fragment_shader_path"];
    sky_vertex_shader_path = config["shading"]["sky_vertex_shader_path"];
    texture_atlas_path = config["shading"]["texture_atlas_path"];
    skybox_faces_paths[0] = config["shading"]["sky_faces_paths"][0];
    skybox_faces_paths[1] = config["shading"]["sky_faces_paths"][1];
}

Config kGameConfig;
