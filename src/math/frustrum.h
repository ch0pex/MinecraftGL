#pragma once
#include <glm/glm/glm.hpp>
#include "../common/public/common_headers.h"


class Camera;

//Enum with the faces of the frustum
enum Faces {
    Near = 0,
    Far,
    Bottom,
    Top,
    Left,
    Right
};

struct Plane {
    glm::vec3 normal = { 0.f, 1.f, 0.f };
    f32 distance = 0.f;             
};

 class Frustum
{
 public:
     void update(const glm::mat4 projectionMatrix);
     bool isPointInside(glm::vec3 point);
 private:
     Plane planes[6];
     
};

