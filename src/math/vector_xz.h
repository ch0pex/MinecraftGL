#pragma once


#include <GL/glew.h>
#include <functional>
#include "common/public/common_headers.h"

struct VectorXZ {
  i64 x, z;
};

bool operator==(const VectorXZ &left, const VectorXZ &right) noexcept;

namespace std {
template <> struct hash<VectorXZ> {
  size_t operator()(const VectorXZ &vect) const noexcept
  {
    std::hash<decltype(vect.x)> hasher;

    auto hash1 = hasher(vect.x);
    auto hash2 = hasher(vect.z);

    return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
  }
};
} // namespace std

namespace std {
template <> struct hash<glm::vec3> {
  size_t operator()(const glm::vec3 &vect) const noexcept
  {
    std::hash<decltype(vect.x)> hasher;

    auto hash1 = hasher(vect.x);
    auto hash2 = hasher(vect.y);
    auto hash3 = hasher(vect.z);

    return std::hash<decltype(vect.x)>{}(
        (hash1 ^ (hash2 << hash3) ^ hash3));
  }
};
} //