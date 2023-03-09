#pragma once
#include <vector>
#include <typeinfo>
#include "Transform.h"
#include "Component.h"

class GameObject
{
private:
	std::vector<Component*> components;
	int getComponentIndex(Component* _component);


protected:
	GameObject();
	int addComponent(Component* _component);
	int removeComponent(Component* _component);

public: 	
	Transform* transform; 

	~GameObject();
	void update();
	std::vector<Component*> *getComponentsList();


	template<typename T> std::vector<T*> *getComponentsByType();
	
};

