#pragma once
#include "../../rendering/Mesh.hpp"



class Chunklet {

private: 
	bool isBuffered; 
	Mesh mesh;
	void addFace(glm::vec3 position,m); 

public:

	Chunklet();
	~Chunklet();
	void addBlock(glm::vec3 position); 
};