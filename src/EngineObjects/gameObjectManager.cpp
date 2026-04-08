#include "EngineObjects/gameObjectManager.hpp"

GameObjectManager::GameObjectManager()
{
	mainCamera = &camera;
}

GameObject& GameObjectManager::CreateGameObject(const std::string& pName)
{
	gameObjects.emplace_back(pName);
	return gameObjects.back();
}

GameObject& GameObjectManager::CreateGameObject(const std::string & pName, const std::string & pPath)
{
	gameObjects.emplace_back(pName, pPath);
	return gameObjects.back();
}

GameObject& GameObjectManager::CreateGameObject(const std::string & pName, const std::string & pPath,
	const std::string & pTexturePath)
{
	gameObjects.emplace_back(pName, pPath, pTexturePath);
	return gameObjects.back();
}