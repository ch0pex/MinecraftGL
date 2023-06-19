#include "chunklet.h"
#include "../world.h"



Chunklet::Chunklet(World& world, glm::vec3 _position) : 
	world(&world) 
{
	mesh = new Mesh(); 
	position.x = _position.x; 
	position.y = _position.y; 
	position.z = _position.z; 

	blockMap.reserve(CHUNKLET_VOLUME); 

	/*
	for(int i = 0; i < CHUNKLET_VOLUME; i++)
	{
		blockMap[i] = Block(Block::STONE);
	}
	*/	
	/*
	for(int i = 0; i < CHUNKLET_VOLUME; i++)
	{
		int cube = 0; 
		if (blockMap[i] == Block::STONE)
			cube = 1; 
		std::cout << cube << "\n";  
	}
	*/
}


Chunklet::~Chunklet() 
{
	//delete (mesh);
}


void Chunklet::buildMesh()
{
	for (int i = 0; i < CHUNKLET_VOLUME; i++)
	{
	
		int x = i % CHUNK_SIZE;
		int y = i / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (i / CHUNK_SIZE) % CHUNK_SIZE;
		//std::cout << "Block: " << x << ", " << y << ", " << z << std::endl; 
		if(blockMap[i] == Block::STONE) 
			addBlockMesh(glm::vec3(position.x + x, position.y + y, position.z + z));
	}
	
}

glm::vec3 Chunklet::getPosition()
{
	return position;
}


void Chunklet::addBlockMesh(glm::vec3 position)
{

	if(tryToAddFace(BlockFace::FRONT, position))
		addFace(position, FACE_FRONT);

	if(tryToAddFace(BlockFace::BACK, position))
		addFace(position, FACE_BACK);

	if(tryToAddFace(BlockFace::RIGHT, position))
		addFace(position, FACE_RIGHT);

	if(tryToAddFace(BlockFace::LEFT, position))
		addFace(position, FACE_LEFT);

	if(tryToAddFace(BlockFace::TOP, position))
		addFace(position, FACE_TOP);

	if(tryToAddFace(BlockFace::BOTTOM, position))
		addFace(position, FACE_BOTTOM);

}



void Chunklet::bufferMesh()
{

	if(getFaces() == 0) return;
	glGenVertexArrays(1, &mesh->renderInfo.vao);
	glBindVertexArray(mesh->renderInfo.vao); 

	glGenBuffers(1, &mesh->vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vbo); 
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertices.size(), &mesh->vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &mesh->ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u32) * mesh->indices.size(), &mesh->indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), static_cast<GLvoid*>(0)); 

	glEnableVertexAttribArray(1); 
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Vertex::texCoords))); 

	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
	
	mesh->vertices.clear(); 
	mesh->vertices.shrink_to_fit();
	mesh->indices.clear(); 
	mesh->indices.shrink_to_fit();
}

u32 Chunklet::getFaces()
{
	return mesh->renderInfo.faces;
}



void Chunklet::addFace(glm::vec3 position, const Vertex face[])
{
	mesh->renderInfo.faces++; 
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


bool Chunklet::tryToAddFace(BlockFace blockFace, glm::vec3 blockPos)
{
	glm::vec3 offset = glm::vec3(0, 0, 0);
	switch (blockFace)
	{
	case BlockFace::FRONT:  offset = glm::vec3(0, 0, 1);  break;
	case BlockFace::BACK:   offset = glm::vec3(0, 0, -1); break;
	case BlockFace::RIGHT:  offset = glm::vec3(1, 0, 0);  break;
	case BlockFace::LEFT:   offset = glm::vec3(-1, 0, 0); break;
	case BlockFace::TOP:    offset = glm::vec3(0, 1, 0);  break;
	case BlockFace::BOTTOM: offset = glm::vec3(0, -1, 0); break;
	default: break;
	}

	offset += blockPos; 

	Block block;
	//std::cout << outOfBounds(offset) << "\n"; 
	if(outOfBounds(offset))
		block = world->getBlock(offset); 
		//return true;
		//std::cout << (int) block << "\n"; 
	else
		block = getBlock(offset); 

	if (block == Block::AIR) 
		return true;
	return false; 
}


bool Chunklet::outOfBounds(glm::vec3 blockPos)
{
	bool x = (blockPos.x >= position.x && blockPos.x < position.x + CHUNK_SIZE); 
	bool y = (blockPos.y >= position.y && blockPos.y < position.y + CHUNK_SIZE);
	bool z = (blockPos.z >= position.z && blockPos.z < position.z + CHUNK_SIZE);
	return !(x && y && z); 
}


Block Chunklet::getBlock(glm::vec3 absolutePosition)
{
	int x = absolutePosition.x - position.x;
	int y = absolutePosition.y - position.y;
	int z = absolutePosition.z - position.z;
	int index = x + z * CHUNK_SIZE + y * CHUNK_SIZE * CHUNK_SIZE;
	return blockMap[index];

}

void Chunklet::setBlock(Block block)
{
	//TODO: Set block in position
	blockMap.push_back(block); 
}