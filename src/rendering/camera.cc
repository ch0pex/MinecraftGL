#include "camera.h"
#include "game_engine.h"


Camera::Camera(f32 fov, f32 width, f32 height, f32 near_plane, f32 far_plane, glm::vec3 position) {
  fov_ = fov;
  width = width;
  height = height;
  near_plane_ = near_plane;
  far_plane_ = far_plane;
  position_ = position;
  front_ = glm::vec3(0.0f, 0.0f, -1.0f);
  up_ = glm::vec3(0.0f, 1.0f, 0.0f);
  right_ = glm::normalize(glm::cross(up_, front_));
  first_mouse_ = true;
  yaw_ = 0;
  pitch_ = 0;
  projection_matrix_ = glm::perspective(fov_, width / height, near_plane_, far_plane_);
  CalculateViewProj();
}

void Camera::CalculateViewProj() {
  view_matrix_ = glm::lookAt(position_, position_ + front_, up_);
  view_proj_matrix_ = projection_matrix_ * view_matrix_;
}

glm::mat4 Camera::GetView() {
  return view_matrix_;
}

glm::mat4 Camera::GetProjection() {
  return projection_matrix_;
}

glm::vec3 Camera::GetPosition() {
  return position_;
}

void Camera::SetPosition(glm::vec3 position) {
  position_ = position;
  CalculateViewProj();
  frustum_.Update(view_proj_matrix_);
}


void Camera::SetFront(f64 xpos, f64 ypos) {
  glm::vec3 direction;

  if (first_mouse_) {

    last_x_ = xpos;
    last_y_ = ypos;
    first_mouse_ = false;
  }

  double xoffset = xpos - last_x_;
  double yoffset = last_y_ - ypos;
  last_x_ = xpos;
  last_y_ = ypos;

  double sensitivity = 0.1f;
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw_ += xoffset;
  pitch_ += yoffset;

  if (pitch_ > 89.0f)
    pitch_ = 89.0f;
  if (pitch_ < -89.0f)
    pitch_ = -89.0f;

  direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
  direction.y = sin(glm::radians(pitch_));
  direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));


  front_ = glm::normalize(direction);
  CalculateViewProj();
  frustum_.Update(view_proj_matrix_);
}

float *Camera::GetViewProjValuePtr() {
  return glm::value_ptr(view_proj_matrix_);
}

bool Camera::InFrustum(Chunklet &chunklet) {
  glm::vec3 chunklet_center = chunklet.GetPosition() + glm::vec3(8.f, 8.f, 8.f);
  return frustum_.IsPointInside(chunklet_center) || glm::distance(chunklet_center, position_) < 64.f;
}
