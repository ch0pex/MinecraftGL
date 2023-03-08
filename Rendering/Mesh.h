#pragma once
#include "../Thirdparty/glm/glm/glm.hpp"
#include <vector>

enum class MeshType {
	CUBE,
	PLANE,
	SPHERE,
	TRIANGLE,
	OBJ
};

struct Vertex {
	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec2 texCoords;
};

class Mesh {
public: 
	static void setCubeData(std::vector<Vertex>& _vertices, std::vector<uint32_t>& _indices);
	static void setPlaneData(std::vector<Vertex>& _vertices, std::vector<uint32_t>& _indices);
	static void setSphereData(std::vector<Vertex>& _vertices, std::vector<uint32_t>& _indices);
	static void setOBJData(std::vector<Vertex>& _vertices, std::vector<uint32_t>& _indices, const char* OBJpath);
};