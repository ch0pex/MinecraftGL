#include "GameObject.h"

GameObject::GameObject() {
	transform = new Transform(); 
	transform->setGameObject(this); 
}

GameObject::~GameObject() {
	for (Component* component : components)
	{
		delete(component);
	}
}

void GameObject::update() {
	for (Component* component : components) {
		component->update();
	}
}

int GameObject::getComponentIndex(Component* _component)
{
	for (int i = 0; i < components.size(); i++)
	{
		if (components.at(i) == _component) return (i);
	}
	return (-1);
}


int GameObject::addComponent(Component* _component)
{

	if (getComponentIndex(_component) != -1) return (0);
	if (typeid(*_component) == typeid(Transform)) return (0); 
	components.push_back(_component);
	_component->setGameObject(this); 
	return (1);
}

int GameObject::removeComponent(Component* _component)
{
	int index = getComponentIndex(_component);
	if (index == -1) return (0);
	components.erase(components.begin() + index);
}


template<typename T>
std::vector<T*> *GameObject::getComponentsByType()
{
	std::vector<T*> components; 
	for (Component* component : components) {
		if (typeid(*component) == typeid(T)) 
			components.push_back((T*)component);
	}
	return &components;
}

std::vector<Component*> *GameObject::getComponentsList()
{
	return &components;
}



