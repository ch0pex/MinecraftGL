#include "Mesh.h"

void Mesh::setCubeData(std::vector<Vertex>& _vertices, std::vector<uint32_t>& _indices)
{
	std::vector<Vertex> vertices = {

		//front
		{ { 0.0f, 0.0f,1.0f },{0.5f,0.5f,1.0 },{1.0f,0.5f,0.5 }, { 0.0, 1.0 } },
		{ { 0.0f,1.0f,1.0f },{0.5f,0.5f,1.0 },{0.5f,1.0f,0.5 },{ 0.0, 0.0 } },
		{ {1.0f,1.0f,1.0f },{0.5f,0.5f,1.0 },{0.5f,0.5f,1.0 }, { 1.0, 0.0 } },
		{ {1.0f, 0.0f,1.0f },{0.5f,0.5f,1.0 },{1.0f,0.5f,1.0 },{ 1.0, 1.0 } },

		// back 
		{ {1.0, 0.0, 0.0 },{0.5f,0.5f, 0.0 },{1.0f,0.5f,1.0 }, {0.0, 1.0 } }, //4
		{ {1.0f,1.0, 0.0 },{0.5f,0.5f, 0.0 },{0.5f,1.0f,1.0 }, {0.0, 0.0 } }, //5
		{ { 0.0,1.0, 0.0 },{0.5f,0.5f, 0.0 },{0.5f,1.0f,1.0 }, {1.0, 0.0 } }, //6
		{ { 0.0, 0.0, 0.0 },{0.5f,0.5f, 0.0 },{1.0f,0.5f,1.0 },{1.0, 1.0 } }, //7


		//left												    
		{ { 0.0, 0.0, 0.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },{0.0, 1.0 } }, //8
		{ { 0.0f,1.0, 0.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },{0.0, 0.0 } }, //9
		{ { 0.0,1.0,1.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },  {1.0, 0.0 } },   //10
		{ { 0.0, 0.0,1.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 }, {1.0, 1.0 } }, //11

		//right												    
		{ {1.0, 0.0,1.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {0.0, 1.0 } }, // 12
		{ {1.0f,1.0,1.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {0.0, 0.0 } }, //13
		{ {1.0,1.0, 0.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {1.0, 0.0 } }, //14
		{ {1.0, 0.0, 0.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },  {1.0, 1.0 } }, //15

		//top
		{ { 0.0f,1.0f,1.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 },{ 0.0, 1.0 } }, //16
		{ { 0.0f,1.0f, 0.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 0.0 } }, //17
		{ {1.0f,1.0f, 0.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 },{ 1.0, 0.0 } }, //18
		{ {1.0f,1.0f,1.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 }, { 1.0, 1.0 } }, //19

		//bottom 
		{ { 0.0f, 0.0, 0.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 1.0 } }, //20
		{ { 0.0, 0.0,1.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 0.0 } }, //21
		{ {1.0, 0.0,1.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 },  { 1.0, 0.0 } },  //22
		{ {1.0, 0.0, 0.0 },{0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 1.0, 1.0 } }, //23

	};



	std::vector<uint32_t> indices = {

		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		4, 6, 7,

		8, 9, 10,
		8, 10, 11,

		12, 13, 14,
		12, 14, 15,

		16, 17, 18,
		16, 18, 19,

		20, 21, 22,
		20, 22, 23

	};


	_vertices.clear();
	_indices.clear();
	_vertices = vertices;
	_indices = indices;
}


void Mesh::setPlaneData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {


	std::vector<Vertex> _vertices = {

		{ { -1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 0.0 },{ 0.0, 1.0 } },
		{ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 1.0f, 0.0 },{ 0.0, 0.0 } },
		{ { 1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 0.0f, 0.0f, 1.0 },{ 1.0, 0.0 } },
		{ { 1.0f, -1.0f, 0.0f },{ 0.0f, 0.0f, 1.0 },{ 1.0f, 0.0f, 1.0 },{ 1.0, 1.0 } }
	};


	std::vector<uint32_t> _indices = {

		0, 1, 2,
		0, 2, 3
	};

	vertices.clear(); indices.clear();
	vertices = _vertices;
	indices = _indices;

}


void Mesh::setSphereData(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {

	std::vector<Vertex> _vertices;
	std::vector<uint32_t> _indices;

	float latitudeBands = 20.0f;
	float longitudeBands = 20.0f;
	float radius = 1.0f;

	for (float latNumber = 0; latNumber <= latitudeBands; latNumber++) {
		float theta = latNumber * 3.14 / latitudeBands;
		float sinTheta = sin(theta);
		float cosTheta = cos(theta);

		for (float longNumber = 0; longNumber <= longitudeBands; longNumber++) {

			float phi = longNumber * 2 * 3.147 / longitudeBands;
			float sinPhi = sin(phi);
			float cosPhi = cos(phi);

			Vertex vs;

			vs.texCoords.x = (longNumber / longitudeBands); // u
			vs.texCoords.y = (latNumber / latitudeBands);   // v

			vs.normal.x = cosPhi * sinTheta;   // normal x
			vs.normal.y = cosTheta;            // normal y
			vs.normal.z = sinPhi * sinTheta;   // normal z

			vs.color.r = vs.normal.x;
			vs.color.g = vs.normal.y;
			vs.color.b = vs.normal.z;

			vs.position.x = radius * vs.normal.x; // x
			vs.position.y = radius * vs.normal.y; // y
			vs.position.z = radius * vs.normal.z; // z

			_vertices.push_back(vs);
		}
	}

	for (uint32_t latNumber = 0; latNumber < latitudeBands; latNumber++) {
		for (uint32_t longNumber = 0; longNumber < longitudeBands; longNumber++) {
			uint32_t first = (latNumber * (longitudeBands + 1)) + longNumber;
			uint32_t second = first + longitudeBands + 1;

			_indices.push_back(first);
			_indices.push_back(second);
			_indices.push_back(first + 1);

			_indices.push_back(second);
			_indices.push_back(second + 1);
			_indices.push_back(first + 1);

		}
	}

	vertices.clear(); indices.clear();
	vertices = _vertices;
	indices = _indices;
}
void Mesh::setOBJData(std::vector<Vertex>& _vertices, std::vector<uint32_t>& _indices, const char* OBJpath)
{

}
