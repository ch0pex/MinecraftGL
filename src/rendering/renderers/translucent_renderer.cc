#include "translucent_renderer.h"
#include "config/config.h"

void TranslucentRenderer::Render(Camera &camera) {
  glDisable(GL_CULL_FACE);
  glEnable(GL_BLEND);

  u32 vp_loc = glGetUniformLocation(shader_, "vp");
  u32 opacity_loc = glGetUniformLocation(shader_, "opacity");

  glUseProgram(shader_);
  glUniformMatrix4fv(vp_loc, 1, GL_FALSE, camera.GetViewProjValuePtr());
  glUniform1f(opacity_loc, kGameConfig.water_opacity);

  glBindTexture(GL_TEXTURE_2D, texture_);

  for (const auto &mesh: meshes_) {
    glBindVertexArray(mesh->vao);
    glDrawElements(GL_TRIANGLES, mesh->faces * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  }
  meshes_.clear();
}
