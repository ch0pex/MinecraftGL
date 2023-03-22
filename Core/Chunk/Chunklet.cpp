#include "Chunklet.h"
#include <iostream>

void Chunklet::addBlock(glm::vec3 blockPos, u32 index)
{
	static Vertex face_front[4] = {
		{ { 0.0f, 0.0f,1.0f },{0.5f,0.5f,1.0 },{1.0f,0.5f,0.5 }, { 0.0, 1.0 } },
		{ { 0.0f,1.0f,1.0f },{0.5f,0.5f,1.0 },{0.5f,1.0f,0.5 },{ 0.0, 0.0 } },
		{ {1.0f,1.0f,1.0f },{0.5f,0.5f,1.0 },{0.5f,0.5f,1.0 }, { 1.0, 0.0 } },
		{ {1.0f, 0.0f,1.0f },{0.5f,0.5f,1.0 },{1.0f,0.5f,1.0 },{ 1.0, 1.0 } }
	};

	static Vertex face_back[4] = {
			{ {1.0, 0.0, 0.0 },{0.5f,0.5f, 0.0 },{1.0f,0.5f,1.0 }, {0.0, 1.0 } }, //4
			{ {1.0f,1.0, 0.0 },{0.5f,0.5f, 0.0 },{0.5f,1.0f,1.0 }, {0.0, 0.0 } }, //5
			{ { 0.0,1.0, 0.0 },{0.5f,0.5f, 0.0 },{0.5f,1.0f,1.0 }, {1.0, 0.0 } }, //6
			{ { 0.0, 0.0, 0.0 },{0.5f,0.5f, 0.0 },{1.0f,0.5f,1.0 },{1.0, 1.0 } }
	};


	static Vertex face_left[4] = {
			{ { 0.0, 0.0, 0.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },{0.0, 1.0 } }, //8
			{ { 0.0f,1.0, 0.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },{0.0, 0.0 } }, //9
			{ { 0.0,1.0,1.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },  {1.0, 0.0 } },   //10
			{ { 0.0, 0.0,1.0 },{ 0.0f,0.5f,0.5 },{0.5f,0.5f,1.0 }, {1.0, 1.0 } }//11
	};

	static Vertex face_right[4] = {
			{ {1.0, 0.0,1.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {0.0, 1.0 } }, // 12
			{ {1.0f,1.0,1.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {0.0, 0.0 } }, //13
			{ {1.0,1.0, 0.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },   {1.0, 0.0 } }, //14
			{ {1.0, 0.0, 0.0 },{1.0f,0.5f,0.5 },{0.5f,0.5f,1.0 },  {1.0, 1.0 } } //15
	};

	static Vertex face_top[4] = {
			{ { 0.0f,1.0f,1.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 },{ 0.0, 1.0 } }, //16
			{ { 0.0f,1.0f, 0.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 0.0 } }, //17
			{ {1.0f,1.0f, 0.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 },{ 1.0, 0.0 } }, //18
			{ {1.0f,1.0f,1.0f },{0.5f,1.0f,0.5 },{0.5f,0.5f,1.0 }, { 1.0, 1.0 } } //19
	};

	static Vertex face_bottom[4] = {
			{ { 0.0f, 0.0, 0.0 }, {0.5f, 0.0f,0.5 }, {0.5f,0.5f,1.0 }, { 0.0, 1.0 } }, //20
			{ { 0.0, 0.0,1.0 }, {0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 0.0, 0.0 } }, //21
			{ {1.0, 0.0,1.0 }, {0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 },  { 1.0, 0.0 } },  //22
			{ {1.0, 0.0, 0.0 }, {0.5f, 0.0f,0.5 },{0.5f,0.5f,1.0 }, { 1.0, 1.0 } } //23
	};


	addFace(blockPos, face_front, index);
	addFace(blockPos, face_back, index);
	addFace(blockPos, face_left, index);
	addFace(blockPos, face_right, index);
	addFace(blockPos, face_bottom, index);
	addFace(blockPos, face_top, index);
}

void Chunklet::addFace(glm::vec3 blockPos, Vertex face[4],u32 index)
{
	//std::cout << position.x + blockPos.x << ", " << position.y + blockPos.y << ", " << position.z + blockPos.z << std::endl; 
	for (size_t i = 0; i < 4; i++)
	{
		face[i].position += position + blockPos;
		solidMesh.vertices.push_back(face[i]);
		solidMesh.indices.push_back(index + i); 

	}	
}


void Chunklet::bufferChunklet()
{
	glGenVertexArrays(1, &solidMesh.vao);
	glBindVertexArray(solidMesh.vao);

	glGenBuffers(1, &solidMesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, solidMesh.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * solidMesh.vertices.size(), &solidMesh.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &solidMesh.ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, solidMesh.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * solidMesh.indices.size(), &solidMesh.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}


Chunklet::Chunklet(glm::vec3 _position, std::vector<Block>& blocks) :
	position(_position),
	blocksLayout(blocks)

{
	solidMesh = Mesh(); 
	// Build mesh TODO: just build faces that face to air 
	for (int i = 0; i < CHUNKLET_VOLUME; i++)
	{
		if (blocksLayout.at(i) == AIR) continue;
		int x = i % CHUNK_SIZE;
		int y = i / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (i / CHUNK_SIZE) % CHUNK_SIZE;
		//std::cout << "Block: " << x << ", " << y << ", " << z << std::endl; 

		addBlock(glm::vec3(x, y, z), i);
	}

	bufferChunklet(); 
	
}
