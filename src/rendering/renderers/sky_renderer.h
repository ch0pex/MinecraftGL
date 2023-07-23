#pragma once 

#include "base_renderer.h"

class SkyRenderer : public BaseRenderer
{
public:
    void BufferSkyMesh();
    ~SkyRenderer();
    void Render(Camera &camera) override;
private: 
    Mesh sky_mesh_;
};


