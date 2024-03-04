#pragma once
#include "glm/vec3.hpp"
#include <glm/gtc/quaternion.hpp>

class Transform
{
	glm::vec3 position{ 1 };
	glm::quat rotation{};
	glm::vec3 scale { 1 };

public:

	Transform();

	[[nodiscard]] glm::mat4 GetMatrix() const;
};
