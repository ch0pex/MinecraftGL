#include "solid_renderer.h"
#include "config/config.h"

void SolidRenderer::Render(Camera &camera) {
  if (meshes_.empty())
    return;

  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);

  u32 vp_loc = glGetUniformLocation(shader_, "vp");
  u32 ambient_color_loc = glGetUniformLocation(shader_, "ambientColor");
  u32 ambient_light_intensity = glGetUniformLocation(shader_, "ambientLightIntensity");
  u32 sun_light_dir_loc = glGetUniformLocation(shader_, "sunLightDirection");
  u32 sun_light_color_loc = glGetUniformLocation(shader_, "sunLightColor");
  u32 sun_light_intensity_loc = glGetUniformLocation(shader_, "sunLightIntensity");

  glUseProgram(shader_);
  glUniformMatrix4fv(vp_loc, 1, GL_FALSE, camera.GetViewProjValuePtr());
  glUniform1f(ambient_light_intensity, kGameConfig.ambient_light_intensity * 0.01f);
  glUniform3f(ambient_color_loc, kGameConfig.ambient_light_color.x, kGameConfig.ambient_light_color.y,
              kGameConfig.ambient_light_color.z);
  glUniform3f(sun_light_dir_loc, kGameConfig.sun_light_direction.x, kGameConfig.sun_light_direction.y,
              kGameConfig.sun_light_direction.z);
  glUniform3f(sun_light_color_loc, kGameConfig.sun_light_color.x, kGameConfig.sun_light_color.y,
              kGameConfig.sun_light_color.z);
  glUniform1f(sun_light_intensity_loc, kGameConfig.sun_light_intensity * 0.01f);

  glBindTexture(GL_TEXTURE_2D, texture_);

  for (const auto &mesh: meshes_) {
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->faces * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
  meshes_.clear();
}