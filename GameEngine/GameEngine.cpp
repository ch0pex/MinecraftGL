#include "GameEngine.h"

GameEngine::GameEngine()
{

}

GameEngine::~GameEngine()
{
	for (GameObject *gameObject : gameObjects)
		delete(gameObject); 
}

std::vector<GameObject*>* GameEngine::getGameObjects()
{
	return &gameObjects;
}

int GameEngine::removeGameObject(GameObject* _gameObject)
{
	return(1); 
}

int GameEngine::addGameObject(GameObject* _gameObject)
{
	gameObjects.push_back(_gameObject);
	return (1); 
}