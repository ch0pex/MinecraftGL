#include "Block.h"



Block::Block(Camera* camera, GLuint texture, GLuint program) : GameObject() {
	MeshRenderer* mesh = new MeshRenderer(this, camera, MeshType::CUBE);
	mesh->setProgram(program); 
	mesh->setTexture(texture); 


	addComponent(mesh);
}

Block::~Block() {

}

