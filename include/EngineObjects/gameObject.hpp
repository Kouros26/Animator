#pragma once
#include <memory>

#include "transform.hpp"
#include "Animation/animator.hpp"
#include "Resources/model.hpp"

class GameObject
{
protected:
	inline static unsigned objectCount = 0;

	unsigned id = 0;

	std::string name;

	Transform transform{};
	Model model{};
	Animator* animator { nullptr };

public:

	GameObject(const std::string& pName);
	GameObject(const std::string& pName, const std::string& pPath);
	GameObject(const std::string& pName, const std::string& pPath, const std::string& pTexturePath);

	void CreateAnimator() const;

	[[nodiscard]] Transform& GetTransform();
	[[nodiscard]] Model& GetModel();
	[[nodiscard]] Animator*& GetAnimator();
};