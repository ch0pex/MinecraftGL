#pragma once

#include <glm/glm/glm.hpp>
#include "../common/public/common_headers.h"


class Camera;

//Enum with the faces_ of the frustum_
enum Faces {
    kNear = 0,
    kFar,
    kBottom,
    kTop,
    kLeft,
    kRight
};

struct Plane {
    glm::vec3 normal = {0.f, 1.f, 0.f};
    f32 distance = 0.f;
};

class Frustum {
public:
    void Update(const glm::mat4 &projection_matrix);
    bool IsPointInside(glm::vec3 point);
private:
    Plane planes_[6];

};
