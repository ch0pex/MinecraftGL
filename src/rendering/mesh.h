#pragma once

#include "../common/public/common_headers.h"
#include <glm/glm/glm.hpp>
#include <vector>


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 color;
    glm::vec2 tex_coords;
};

struct RenderInfo {
    u32 vao, faces;
};

struct Mesh {
    RenderInfo render_info;
    u32 vbo, ebo;
    std::vector<Vertex> vertices;
    std::vector<u32> indices;
};


constexpr Vertex kFaceFront[4] = {
        {{0.0f, 0.0f, 1.0f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.5f, 0.5f}, {0.0f, 1.0f}},
        {{0.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 1.0f}, {0.5f, 1.0f, 0.5f}, {0.0f, 0.0f}},
        {{1.0f, 1.0f, 1.0f}, {0.5f, 0.5f, 1.0f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}},
        {{1.0f, 0.0f, 1.0f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.5f, 1.0f}, {1.0f, 1.0f}}
};

constexpr Vertex kFaceBack[4] = {
        {{1.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 0.5f, 1.0f}, {0.0f, 1.0f}}, //4
        {{1.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.5f, 1.0f, 1.0f}, {0.0f, 0.0f}}, //5
        {{0.0f, 1.0f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.5f, 1.0f, 1.0f}, {1.0f, 0.0f}}, //6
        {{0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.0f}, {1.0f, 0.5f, 1.0f}, {1.0f, 1.0f}}
};


constexpr Vertex kFaceLeft[4] = {
        {{0.0f, 0.0f, 0.0f}, {0.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}}, //8
        {{0.0f, 1.0f, 0.0f}, {0.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, //9
        {{0.0f, 1.0f, 1.0f}, {0.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}},   //10
        {{0.0f, 0.0f, 1.0f}, {0.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}}//11
};

constexpr Vertex kFaceRight[4] = {
        {{1.0f, 0.0f, 1.0f}, {1.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}}, // 12
        {{1.0f, 1.0f, 1.0f}, {1.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, //13
        {{1.0f, 1.0f, 0.0f}, {1.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}}, //14
        {{1.0f, 0.0f, 0.0f}, {1.0f, 0.5f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}} //15
};

constexpr Vertex kFaceTop[4] = {
        {{0.0f, 1.0f, 1.0f}, {0.5f, 1.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}}, //16
        {{0.0f, 1.0f, 0.0f}, {0.5f, 1.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, //17
        {{1.0f, 1.0f, 0.0f}, {0.5f, 1.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}}, //18
        {{1.0f, 1.0f, 1.0f}, {0.5f, 1.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}} //19
};

constexpr Vertex kFaceBottom[4] = {
        {{0.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 1.0f}}, //20
        {{0.0f, 0.0f, 1.0f}, {0.5f, 0.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {0.0f, 0.0f}}, //21
        {{1.0f, 0.0f, 1.0f}, {0.5f, 0.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 0.0f}},  //22
        {{1.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.5f}, {0.5f, 0.5f, 1.0f}, {1.0f, 1.0f}} //23
};


constexpr u32 kFaceIndex[6] = {
        0, 1, 2,
        0, 2, 3
};

