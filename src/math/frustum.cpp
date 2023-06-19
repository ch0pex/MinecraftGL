#include <algorithm>

#include "frustrum.h"
#include "../rendering/Camera.h"


void Frustum::update(const glm::mat4 projectionMatrix)
{

    planes[Faces::Near].normal.x = projectionMatrix[0][3] + projectionMatrix[0][2];
    planes[Faces::Near].normal.y = projectionMatrix[1][3] + projectionMatrix[1][2];
    planes[Faces::Near].normal.z = projectionMatrix[2][3] + projectionMatrix[2][2];
    planes[Faces::Near].distance = projectionMatrix[3][3] + projectionMatrix[3][2];
    
    planes[Faces::Far].normal.x = projectionMatrix[0][3] - projectionMatrix[0][2];
    planes[Faces::Far].normal.y = projectionMatrix[1][3] - projectionMatrix[1][2];
    planes[Faces::Far].normal.z = projectionMatrix[2][3] - projectionMatrix[2][2];
    planes[Faces::Far].distance = projectionMatrix[3][3] - projectionMatrix[3][2];
    
    planes[Faces::Left].normal.x = projectionMatrix[0][3] + projectionMatrix[0][0];
    planes[Faces::Left].normal.y = projectionMatrix[1][3] + projectionMatrix[1][0];
    planes[Faces::Left].normal.z = projectionMatrix[2][3] + projectionMatrix[2][0];
    planes[Faces::Left].distance = projectionMatrix[3][3] + projectionMatrix[3][0];
    
    planes[Faces::Right].normal.x = projectionMatrix[0][3] - projectionMatrix[0][0];
    planes[Faces::Right].normal.y = projectionMatrix[1][3] - projectionMatrix[1][0];
    planes[Faces::Right].normal.z = projectionMatrix[2][3] - projectionMatrix[2][0];
    planes[Faces::Right].distance = projectionMatrix[3][3] - projectionMatrix[3][0];
    
    planes[Faces::Bottom].normal.x = projectionMatrix[0][3] + projectionMatrix[0][1];
    planes[Faces::Bottom].normal.y = projectionMatrix[1][3] + projectionMatrix[1][1];
    planes[Faces::Bottom].normal.z = projectionMatrix[2][3] + projectionMatrix[2][1];
    planes[Faces::Bottom].distance = projectionMatrix[3][3] + projectionMatrix[3][1];
    
    planes[Faces::Top].normal.x = projectionMatrix[0][3] - projectionMatrix[0][1];
    planes[Faces::Top].normal.y = projectionMatrix[1][3] - projectionMatrix[1][1];
    planes[Faces::Top].normal.z = projectionMatrix[2][3] - projectionMatrix[2][1];
    planes[Faces::Top].distance = projectionMatrix[3][3] - projectionMatrix[3][1];
    
    for (auto &plane : planes) {
        float length = glm::length(plane.normal);
        plane.normal /= length;
        plane.distance /= length;
    }
    
}

bool Frustum::isPointInside(glm::vec3 point)
{
    return std::all_of(std::begin(planes), std::end(planes), [&](Plane plane) {
        return (glm::dot(point, plane.normal) + plane.distance >= -16.0f); 
    });
}

