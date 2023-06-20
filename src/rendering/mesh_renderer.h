#pragma once

#include <vector>
#include <glm/glm/gtc/type_ptr.hpp>
#include "mesh.h"
#include "camera.h"
#include "../common/public/common_headers.h"


class MeshRenderer {

private:
    std::vector<RenderInfo *> meshes_;
    u32 texture_, shader_;


public:
    MeshRenderer();
    ~MeshRenderer();

    void SetTexture(u32 texture);
    void SetShader(u32 shader);

    void AddMesh(RenderInfo *mesh);
    void Render(Camera &camera);

    void AddReferenceMesh();

};