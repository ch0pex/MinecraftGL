#pragma once


class GameObject; 

class Component
{
protected:
	GameObject* gameObject;

public:

	void setGameObject(GameObject* _gameObject);
	virtual void update() = 0;
};


