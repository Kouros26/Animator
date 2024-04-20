#include "EngineObjects/gameObject.hpp"

#include "Resources/resourceManager.hpp"

GameObject::GameObject(const std::string& pName)
	: id(objectCount), name(pName)
{
	model = Model("resources/models/cube.obj");
	objectCount++;
}

GameObject::GameObject(const std::string& pName, const std::string& pPath)
{
	model = Model(pPath);
	objectCount++;
}

GameObject::GameObject(const std::string& pName, const std::string& pPath, const std::string& pTexturePath)
	: GameObject(pName, pPath)
{
	
}

void GameObject::CreateAnimator() const
{
	*animator = Animator(nullptr);
}

Transform& GameObject::GetTransform()
{
	return transform;
}

Model& GameObject::GetModel()
{
	return model;
}

Animator*& GameObject::GetAnimator()
{
	return animator;
}
