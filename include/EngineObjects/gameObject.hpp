#pragma once
#include "transform.hpp"

class GameObject
{
	Transform transform{};

public:

	Transform& GetTransform();
};
