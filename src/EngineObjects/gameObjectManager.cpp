#include "EngineObjects/gameObjectManager.hpp"

GameObject& GameObjectManager::CreateGameObject(const std::string& pName)
{
	gameObjects.emplace_back(pName);
	return gameObjects[gameObjects.size() - 1];
}

std::vector<GameObject>& GameObjectManager::GetGameObjects()
{
	return gameObjects;
}
