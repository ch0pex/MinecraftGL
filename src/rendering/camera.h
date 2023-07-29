#pragma once

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include "common/public/common_headers.h"
#include "math/frustrum.h"
#include "world/Chunk/chunklet.h"
#include <mutex>


class GameEngine;

class Camera {
public:
  Camera(f32 fov, f32 width, f32 height, f32 near_plane, f32 far_plane, glm::vec3 position);
  ~Camera() = default;

  glm::mat4 GetView();
  glm::mat4 GetProjection();


  glm::vec3 GetPosition();
  void SetPosition(glm::vec3 position);
  void SetFront(f64 xpos, f64 ypos);

  float *GetViewProjValuePtr();
  bool InFrustum(Chunklet &chunklet);

  friend class Frustum;
  friend class Player;
private:

  Frustum frustum_;

  glm::mat4 view_matrix_, projection_matrix_, view_proj_matrix_;
  glm::vec3 position_, front_, up_, right_;

  f32 fov_;
  f32 width_;
  f32 height_;
  f32 near_plane_;
  f32 far_plane_;

  bool first_mouse_;
  f64 last_x_;
  f64 last_y_;
  f64 yaw_;
  f64 pitch_;

  void CalculateViewProj();
};

