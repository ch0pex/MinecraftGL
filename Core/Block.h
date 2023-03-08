#pragma once
#include "GameObject.h"
#include "../Rendering/MeshRenderer.h"	


class Block : public GameObject
{

public:
	Block(Camera* camera, GLuint texture, GLuint program);
	~Block();
};

