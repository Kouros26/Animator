#pragma once
#include <glm/glm.hpp>

#include "EngineObjects/gameObject.hpp"
#include "glm/ext/matrix_clip_space.hpp"

class Camera : public GameObject
{
	glm::mat4 view{ 1 };

	glm::mat4 projection{ 1 };

public:

	Camera();

	constexpr glm::mat4 GetProjectionMatrix() const;
};

constexpr glm::mat4 Camera::GetProjectionMatrix() const
{
	return projection;
}
