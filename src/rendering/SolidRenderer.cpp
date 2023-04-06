#include "SolidRenderer.h"

SolidRenderer::SolidRenderer() 
{

}

SolidRenderer::~SolidRenderer() 
{

}

void SolidRenderer::addMesh(Mesh* mesh)
{
	meshes.push_back(mesh);
}

void SolidRenderer::render(Camera& camera)
{
	
}