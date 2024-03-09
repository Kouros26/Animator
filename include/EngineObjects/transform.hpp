#pragma once
#include "glm/vec3.hpp"
#include <glm/gtc/quaternion.hpp>

#define GLM_ENABLE_EXPERIMENTAL 1

#include "glm/gtx/quaternion.hpp"

class Transform
{
	glm::vec3 position{};
	glm::quat rotation{};
	glm::vec3 scale { 1 };

public:

	Transform();

	[[nodiscard]] glm::mat4 GetMatrix() const;

	[[nodiscard]] constexpr glm::vec3 GetPosition() const;

	constexpr void AddPosition(const glm::vec3& delta);

	constexpr void SetPosition(const glm::vec3& pPosition);
};

constexpr glm::vec3 Transform::GetPosition() const
{
	return position;
}

constexpr void Transform::AddPosition(const glm::vec3& delta)
{
	position += delta;
}

constexpr void Transform::SetPosition(const glm::vec3& pPosition)
{
	position = pPosition;
}
