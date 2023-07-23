#include "render_engine.h"
#include "../loaders/shader_loader.h"
#include "../loaders/texture_loader.h"
#include "../config/config.h"

RenderEngine::RenderEngine()
{
	if (!glfwInit())
		std::terminate();

	// Crea una ventana de GLFW
	window_ = glfwCreateWindow(1920, 1080, "CraftGL", NULL, NULL);

	if (!window_)
	{
		glfwTerminate();
		std::terminate();
	}

	// Hace que la ventana sea el contexto actual
	glfwMakeContextCurrent(window_);

	// Inicializa GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		std::terminate();
	}

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	InitializeRenderers();
	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

RenderEngine::~RenderEngine()
{

}

void RenderEngine::InitializeRenderers()
{
	u32 solid_shader, water_shader, sky_shader, atlas, sky_texture;

	solid_shader = ShaderLoader::CreateProgram((kGameConfig.solid_vertex_shader_path).c_str(), (kGameConfig.solid_fragment_shader_path).c_str());
	water_shader = ShaderLoader::CreateProgram((kGameConfig.water_vertex_shader_path).c_str(), (kGameConfig.water_fragment_shader_path).c_str());
	sky_shader = ShaderLoader::CreateProgram((kGameConfig.sky_vertex_shader_path).c_str(), (kGameConfig.sky_fragment_shader_path).c_str());

	atlas = TextureLoader::LoadTexture(kGameConfig.texture_atlas_path);
	sky_texture = TextureLoader::LoadSkyTexture(kGameConfig.skybox_faces_paths);

	sky_renderer_.BufferSkyMesh();
	sky_renderer_.SetTexture(sky_texture);
	sky_renderer_.SetShader(sky_shader);

	solid_renderer_.SetTexture(atlas);
	solid_renderer_.SetShader(solid_shader);

	water_renderer_.SetTexture(atlas);
	water_renderer_.SetShader(water_shader);

	glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void RenderEngine::RenderScene(Camera &camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(kGameConfig.back_ground_color.x, kGameConfig.back_ground_color.y, kGameConfig.back_ground_color.z, kGameConfig.back_ground_color.w);

	solid_renderer_.Render(camera);
	water_renderer_.Render(camera);
	// floraRenderer.Render(camera_);
	sky_renderer_.Render(camera);

	glfwSwapBuffers(window_);
}

void RenderEngine::DrawChunklet(Chunklet &chunklet) 
{
	solid_renderer_.AddMesh(&chunklet.model_.solid_mesh->render_info);
	water_renderer_.AddMesh(&chunklet.model_.water_mesh->render_info);
	//floraRenderer.AddMesh(&chunklet.model_.flora_mesh->render_info);
}


bool RenderEngine::ShouldClose()
{
	return glfwWindowShouldClose(window_);
}


GLFWwindow *RenderEngine::GetWindow() 
{
	return window_;
}
