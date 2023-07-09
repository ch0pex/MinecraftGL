#include "mesh_renderer.h"
#include "../world/chunk/chunklet.h"
#include "../config/config.h"

MeshRenderer::MeshRenderer()
{


}


MeshRenderer::~MeshRenderer()
{

}


void MeshRenderer::AddMesh(RenderInfo *mesh) 
{
    meshes_.push_back(mesh);
}


void MeshRenderer::Render(Camera &camera) 
{
    u32 vp_loc = glGetUniformLocation(shader_, "vp");
    u32 ambient_color_loc = glGetUniformLocation(shader_, "ambientColor"); 
    u32 ambient_light_intensity = glGetUniformLocation(shader_, "ambientLightIntensity");
    u32 sun_light_pos_loc = glGetUniformLocation(shader_, "sunLightPosition");
    u32 sun_light_color_loc = glGetUniformLocation(shader_, "sunLightColor");
    u32 sun_light_intensity_loc = glGetUniformLocation(shader_, "sunLightIntensity");

    glUseProgram(shader_);
    glUniformMatrix4fv(vp_loc, 1, GL_FALSE, camera.GetViewProjValuePtr());
    glUniform1f(ambient_light_intensity, kGameConfig.ambient_light_intensity * 0.01f);
    glUniform3f(ambient_color_loc,kGameConfig.ambient_light_color.x, kGameConfig.ambient_light_color.y, kGameConfig.ambient_light_color.z);
    glUniform3f(sun_light_pos_loc, kGameConfig.sun_light_position.x, kGameConfig.sun_light_position.y, kGameConfig.sun_light_position.z);
    glUniform3f(sun_light_color_loc, kGameConfig.sun_light_color.x, kGameConfig.sun_light_color.y, kGameConfig.sun_light_color.z);
    glUniform1f(sun_light_intensity_loc, kGameConfig.sun_light_intensity * 0.01f);

    glBindTexture(GL_TEXTURE_2D, texture_);

    for (const auto &mesh: meshes_) {
        glBindVertexArray(mesh->vao);
        glDrawElements(GL_TRIANGLES, mesh->faces * 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }
    meshes_.clear();
}

void MeshRenderer::SetTexture(u32 texture) 
{
    texture_ = texture;
}

void MeshRenderer::SetShader(u32 shader) 
{
    shader_ = shader;
}

