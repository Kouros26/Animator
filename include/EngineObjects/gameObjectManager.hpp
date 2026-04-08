#pragma once
#include <vector>

#include "gameObject.hpp"
#include "Rendering/OpenGL/camera.hpp"

class GameObjectManager
{
	Camera camera;  //TODO: Remove camera and constructor to later construct a default scene with json file

public:

	GameObjectManager();

    GameObject& CreateGameObject(const std::string& pName);
    GameObject& CreateGameObject(const std::string& pName, const std::string& pPath);
    GameObject& CreateGameObject(const std::string& pName, const std::string& pPath, const std::string& pTexturePath);
   
    constexpr std::vector<GameObject>& GetGameObjects();
    constexpr Camera& GetMainCamera() const;

private:

	std::vector<GameObject> gameObjects{};

	Camera* mainCamera = nullptr;
};

inline constexpr std::vector<GameObject>& GameObjectManager::GetGameObjects()
{
	return gameObjects;
}

inline constexpr Camera& GameObjectManager::GetMainCamera() const
{
	return *mainCamera;
}