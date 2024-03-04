#pragma once
#include <vector>

#include "gameObject.hpp"

class GameObjectManager
{

public:

	std::vector<GameObject>& GetGameObjects();

private:

	std::vector<GameObject> gameObjects;
};
