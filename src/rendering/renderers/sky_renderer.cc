#include "sky_renderer.h"

void SkyRenderer::BufferSkyMesh() {
  const std::vector<Vertex> vertices = {
      //front
      {{-500.0f, -500.0f, 500.0f},  {0.0f,  0.0f,  1.0},  {1.0f, 0.0f, 0.0}, {0.0, 1.0}},
      {{-500.0f, 500.0f,  500.0f},  {0.0f,  0.0f,  1.0},  {0.0f, 1.0f, 0.0}, {0.0, 0.0}},
      {{500.0f,  500.0f,  500.0f},  {0.0f,  0.0f,  1.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}},
      {{500.0f,  -500.0f, 500.0f},  {0.0f,  0.0f,  1.0},  {1.0f, 0.0f, 1.0}, {1.0, 1.0}},

      // back
      {{500.0,   -500.0,  -500.0},  {0.0f,  0.0f,  -1.0}, {1.0f, 0.0f, 1.0}, {0.0, 1.0}}, //4
      {{500.0f,  500.0,   -500.0},  {0.0f,  0.0f,  -1.0}, {0.0f, 1.0f, 1.0}, {0.0, 0.0}}, //5
      {{-500.0,  500.0,   -500.0},  {0.0f,  0.0f,  -1.0}, {0.0f, 1.0f, 1.0}, {1.0, 0.0}}, //6
      {{-500.0,  -500.0,  -500.0},  {0.0f,  0.0f,  -1.0}, {1.0f, 0.0f, 1.0}, {1.0, 1.0}}, //7


      //left
      {{-500.0,  -500.0,  -500.0},  {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, //8
      {{-500.0f, 500.0,   -500.0},  {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //9
      {{-500.0,  500.0,   500.0},   {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}},   //10
      {{-500.0,  -500.0,  500.0},   {-1.0f, 0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //11

      //right
      {{500.0,   -500.0,  500.0},   {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, // 12
      {{500.0f,  500.0,   500.0},   {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //13
      {{500.0,   500.0,   -500.0},  {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}}, //14
      {{500.0,   -500.0,  -500.0},  {1.0f,  0.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //15

      //top
      {{-500.0f, 500.0f,  500.0f},  {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, //16
      {{-500.0f, 500.0f,  -500.0f}, {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //17
      {{500.0f,  500.0f,  -500.0f}, {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}}, //18
      {{500.0f,  500.0f,  500.0f},  {0.0f,  1.0f,  0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //19

      //bottom
      {{-500.0f, -500.0,  -500.0},  {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {0.0, 1.0}}, //20
      {{-500.0,  -500.0,  500.0},   {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {0.0, 0.0}}, //21
      {{500.0,   -500.0,  500.0},   {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {1.0, 0.0}},  //22
      {{500.0,   -500.0,  -500.0},  {0.0f,  -1.0f, 0.0},  {0.0f, 0.0f, 1.0}, {1.0, 1.0}}, //23

  };

  const std::vector<u32> indices = {

      0, 1, 2,
      2, 3, 0,

      4, 5, 6,
      4, 6, 7,

      8, 9, 10,
      8, 10, 11,

      12, 13, 14,
      12, 14, 15,

      16, 17, 18,
      16, 18, 19,

      20, 21, 22,
      20, 22, 23

  };


  sky_mesh_.vertices.clear();
  sky_mesh_.indices.clear();
  sky_mesh_.vertices = vertices;
  sky_mesh_.indices = indices;

  glGenVertexArrays(1, &sky_mesh_.render_info.vao);
  glBindVertexArray(sky_mesh_.render_info.vao);

  glGenBuffers(1, &sky_mesh_.vbo);
  glBindBuffer(GL_ARRAY_BUFFER, sky_mesh_.vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * sky_mesh_.vertices.size(), &sky_mesh_.vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &sky_mesh_.ebo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, sky_mesh_.ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * sky_mesh_.indices.size(), &sky_mesh_.indices[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);

  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) (offsetof(Vertex, Vertex::tex_coords)));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  meshes_.push_back(&sky_mesh_.render_info);
}


SkyRenderer::~SkyRenderer() {

}

void SkyRenderer::Render(Camera &camera) {
  u32 vp_loc = glGetUniformLocation(shader_, "vp");
  glm::mat4 vp = glm::mat4(glm::mat3(camera.GetView())) * camera.GetProjection();

  glDisable(GL_BLEND);
  glEnable(GL_CULL_FACE);

  glDepthFunc(GL_LEQUAL);
  glUseProgram(shader_);
  glUniformMatrix4fv(vp_loc, 1, GL_FALSE, &vp[0][0]);

  glBindVertexArray(meshes_[0]->vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, texture_);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
}