#pragma once
#include "glm/mat4x4.hpp"

struct BoneInfo
{
	int id;

	glm::mat4 offset;
};
