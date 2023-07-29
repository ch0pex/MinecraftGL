#include "frustrum.h"

#include <algorithm>

void Frustum::Update(const glm::mat4 &projection_matrix) {

  planes_[Faces::kNear].normal.x = projection_matrix[0][3] + projection_matrix[0][2];
  planes_[Faces::kNear].normal.y = projection_matrix[1][3] + projection_matrix[1][2];
  planes_[Faces::kNear].normal.z = projection_matrix[2][3] + projection_matrix[2][2];
  planes_[Faces::kNear].distance = projection_matrix[3][3] + projection_matrix[3][2];

  planes_[Faces::kFar].normal.x = projection_matrix[0][3] - projection_matrix[0][2];
  planes_[Faces::kFar].normal.y = projection_matrix[1][3] - projection_matrix[1][2];
  planes_[Faces::kFar].normal.z = projection_matrix[2][3] - projection_matrix[2][2];
  planes_[Faces::kFar].distance = projection_matrix[3][3] - projection_matrix[3][2];

  planes_[Faces::kLeft].normal.x = projection_matrix[0][3] + projection_matrix[0][0];
  planes_[Faces::kLeft].normal.y = projection_matrix[1][3] + projection_matrix[1][0];
  planes_[Faces::kLeft].normal.z = projection_matrix[2][3] + projection_matrix[2][0];
  planes_[Faces::kLeft].distance = projection_matrix[3][3] + projection_matrix[3][0];

  planes_[Faces::kRight].normal.x = projection_matrix[0][3] - projection_matrix[0][0];
  planes_[Faces::kRight].normal.y = projection_matrix[1][3] - projection_matrix[1][0];
  planes_[Faces::kRight].normal.z = projection_matrix[2][3] - projection_matrix[2][0];
  planes_[Faces::kRight].distance = projection_matrix[3][3] - projection_matrix[3][0];

  planes_[Faces::kBottom].normal.x = projection_matrix[0][3] + projection_matrix[0][1];
  planes_[Faces::kBottom].normal.y = projection_matrix[1][3] + projection_matrix[1][1];
  planes_[Faces::kBottom].normal.z = projection_matrix[2][3] + projection_matrix[2][1];
  planes_[Faces::kBottom].distance = projection_matrix[3][3] + projection_matrix[3][1];

  planes_[Faces::kTop].normal.x = projection_matrix[0][3] - projection_matrix[0][1];
  planes_[Faces::kTop].normal.y = projection_matrix[1][3] - projection_matrix[1][1];
  planes_[Faces::kTop].normal.z = projection_matrix[2][3] - projection_matrix[2][1];
  planes_[Faces::kTop].distance = projection_matrix[3][3] - projection_matrix[3][1];

  for (auto &plane: planes_) {
    float length = glm::length(plane.normal);
    plane.normal /= length;
    plane.distance /= length;
  }

}

bool Frustum::IsPointInside(glm::vec3 point) {
  return std::all_of(std::begin(planes_), std::end(planes_), [&](Plane plane) {
    return (glm::dot(point, plane.normal) + plane.distance >= -24.0f);
  });
}

