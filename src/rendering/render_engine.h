#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "camera.h"
#include "mesh_renderer.h"
#include "../world/chunk/chunklet.h"


class RenderEngine {
private:
    GLFWwindow *window_;
    MeshRenderer solid_renderer_;
    //MeshRenderer waterRenderer;

public:
    RenderEngine();
    ~RenderEngine();

    void RenderScene(Camera &camera);
    bool ShouldClose();

    void DrawChunklet(Chunklet &chunklet);
    GLFWwindow *GetWindow();

};