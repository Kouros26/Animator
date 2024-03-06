#include "EngineObjects/gameObject.hpp"

GameObject::GameObject(const std::string& pName)
	: id(objectCount), name(pName)
{
	objectCount++;
}

Transform& GameObject::GetTransform()
{
	return transform;
}

const Model& GameObject::GetModel() const
{
	return model;
}
