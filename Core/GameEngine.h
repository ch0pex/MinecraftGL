#pragma once
#include <vector>
#include "GameObject.h"
#include "../Util/Singleton.hpp"
//#include "WorldGenerator.h"

class GameEngine : public Singleton<GameEngine>
{
private:
	std::vector<GameObject*> gameObjects;
	//WorldGenerator* worldGenerator;
public:
	GameEngine();
	~GameEngine();
	std::vector<GameObject*>* getGameObjects();
	int removeGameObject(GameObject* _gameObject);
	int addGameObject(GameObject* _gameObject);
};
