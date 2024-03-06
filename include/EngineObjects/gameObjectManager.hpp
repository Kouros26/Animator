#pragma once
#include <vector>

#include "gameObject.hpp"

class GameObjectManager
{

public:

	GameObject& CreateGameObject(const std::string& pName);

	std::vector<GameObject>& GetGameObjects();

private:

	std::vector<GameObject> gameObjects{};
};
