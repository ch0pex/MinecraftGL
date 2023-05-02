#pragma once
#include <glm/glm/glm.hpp>
#include "../world/chunk/chunklet.h"

class Camera;

struct Plane
{
    // unit vector
    glm::vec3 normal = { 0.f, 1.f, 0.f };

    // distance from origin to the nearest point in the plane
    float distance = 0.f;             
};

 class Frustum
{
 private:
    Plane topFace;
    Plane bottomFace;

    Plane rightFace;
    Plane leftFace;

    Plane farFace;
    Plane nearFace;
 public:
     void update(Camera& camera);

     
     
};

