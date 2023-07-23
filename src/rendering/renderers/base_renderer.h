#pragma once

#include <vector>
#include <glm/glm/gtc/type_ptr.hpp>
#include "../mesh.h"
#include "../camera.h"
#include "../../common/public/common_headers.h"

class BaseRenderer {
protected:
    std::vector<RenderInfo *> meshes_;
    u32 texture_, shader_;

public:
    inline void SetTexture(u32 texture) { texture_ = texture; }
    inline void SetShader(u32 shader) { shader_ = shader; }

    inline void AddMesh(RenderInfo *mesh) { meshes_.push_back(mesh);}
    virtual void Render(Camera &camera) = 0;

};
