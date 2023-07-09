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
        // Manejo de error
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
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);


    u32 shader = ShaderLoader::CreateProgram((kGameConfig.solid_vertex_shader_path).c_str(), (kGameConfig.solid_fragment_shader_path).c_str());
    u32 texture = TextureLoader::LoadTexture(kGameConfig.texture_atlas_path);

    solid_renderer_.SetTexture(texture);
    solid_renderer_.SetShader(shader);
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}


RenderEngine::~RenderEngine()
{

}


void RenderEngine::RenderScene(Camera &camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(kGameConfig.back_ground_color.x, kGameConfig.back_ground_color.y, kGameConfig.back_ground_color.z, kGameConfig.back_ground_color.w);

    solid_renderer_.Render(camera);
    //waterRenderer.Render(camera_);
    //floraRenderer.Render(camera_);

    glfwSwapBuffers(window_);
}


void RenderEngine::DrawChunklet(Chunklet &chunklet) {
    solid_renderer_.AddMesh(&chunklet.mesh_->render_info);
    //waterRenderer.AddMesh(&chunklet.waterMesh->render_info);
    //floraRenderer.AddMesh(&chunklet.floraMesh->render_info);
}


bool RenderEngine::ShouldClose() {
    return glfwWindowShouldClose(window_);
}


GLFWwindow *RenderEngine::GetWindow() {
    return window_;
}
