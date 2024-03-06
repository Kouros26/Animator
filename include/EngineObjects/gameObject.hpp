#pragma once
#include "transform.hpp"
#include "Resources/model.hpp"

class GameObject
{
	inline static unsigned objectCount = 0;

	unsigned id = 0;

	std::string name;

	Transform transform{};
	Model model{};

public:

	GameObject(const std::string& pName);

	Transform& GetTransform();
	const Model& GetModel() const;
};
