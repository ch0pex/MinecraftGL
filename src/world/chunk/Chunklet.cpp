#include "Chunklet.h"

Chunklet::Chunklet(glm::vec3 _position) : 
	isBuffered(false)
{
	mesh = new Mesh(); 
	position.x = _position.x * CHUNK_SIZE; 
	position.y = _position.y * CHUNK_SIZE; 
	position.z = _position.z * CHUNK_SIZE; 



	for (int i = 0; i < CHUNKLET_VOLUME; i++)
	{
	
		int x = i % CHUNK_SIZE;
		int y = i / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (i / CHUNK_SIZE) % CHUNK_SIZE;
		//std::cout << "Block: " << x << ", " << y << ", " << z << std::endl; 
		addBlock(glm::vec3(position.x + x, position.y + y, position.z + z));
	}



}

Chunklet::~Chunklet() 
{

}


void Chunklet::addBlock(glm::vec3 position)
{

	addFace(position, FACE_FRONT);
	addFace(position, FACE_BACK);
	addFace(position, FACE_RIGHT);
	addFace(position, FACE_LEFT);
	addFace(position, FACE_TOP);
	addFace(position, FACE_BOTTOM);
}


void Chunklet::addFace(glm::vec3 position, const Vertex face[])
{
	u32 index_offset = mesh->vertices.size(); 
	for (int i = 0; i < 6; i++)
	{
		if(i < 4){
			Vertex vertex = face[i];
			vertex.position += position;
			mesh->vertices.push_back(vertex);
		}
		mesh->indices.push_back(FACE_INDEX[i] + index_offset);

	}
}

void Chunklet::bufferMesh()
{
	isBuffered = true; 
	glGenVertexArrays(1, &mesh->vao);
	glBindVertexArray(mesh->vao); 


	glGenBuffers(1, &mesh->vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	

	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); 

	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords))); 

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	/*
	mesh->vertices.clear(); 
	mesh->vertices.shrink_to_fit();
	mesh->indices.clear(); 
	mesh->indices.shrink_to_fit();
	*/
	

}
