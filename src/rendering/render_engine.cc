#include "render_engine.h"

#include "../loaders/shader_loader.h"
#include "../loaders/texture_loader.h"


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


    u32 shader = ShaderLoader::CreateProgram("res/shaders/solidShader.vs", "res/shaders/solidShader.fs");
    u32 texture = TextureLoader::LoadTexture("res/textures/stone.jpg");

    solid_renderer_.SetTexture(texture);
    solid_renderer_.SetShader(shader);
    solid_renderer_.AddReferenceMesh();
    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}


RenderEngine::~RenderEngine()
{

}


void RenderEngine::RenderScene(Camera &camera)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.4f, 5.0f, 0.75f, 1.0);

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
