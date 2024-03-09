#pragma once
#include <vector>

#include "gameObject.hpp"
#include "Rendering/OpenGL/camera.hpp"

class GameObjectManager
{
	Camera camera;  //TODO: Remove camera and constructor to later construct a default scene with json file

public:

	GameObjectManager();

    constexpr GameObject& CreateGameObject(const std::string& pName);
    constexpr GameObject& CreateGameObject(const std::string& pName, const std::string& pPath);
    constexpr GameObject& CreateGameObject(const std::string& pName, const std::string& pPath, const std::string& pTexturePath);
   
    constexpr std::vector<GameObject>& GetGameObjects();
    constexpr Camera& GetMainCamera() const;

private:

	std::vector<GameObject> gameObjects{};

	Camera* mainCamera = nullptr;
};

constexpr GameObject& GameObjectManager::CreateGameObject(const std::string& pName)
{
	gameObjects.emplace_back(pName);
	return gameObjects[gameObjects.size() - 1];
}

constexpr GameObject& GameObjectManager::CreateGameObject(const std::string& pName, const std::string& pPath)
{
	gameObjects.emplace_back(pName, pPath);
	return gameObjects[gameObjects.size() - 1];
}

constexpr GameObject& GameObjectManager::CreateGameObject(const std::string& pName, const std::string& pPath,
	const std::string& pTexturePath)
{
	gameObjects.emplace_back(pName, pPath);
	return gameObjects[gameObjects.size() - 1];
}

constexpr std::vector<GameObject>& GameObjectManager::GetGameObjects()
{
	return gameObjects;
}

constexpr Camera& GameObjectManager::GetMainCamera() const
{
	return *mainCamera;
}
