#pragma once
#include "blender.hpp"
#include "GLFW/glfw3.h"

class UIManager
{
	Blender blender;

public:

	UIManager();
	UIManager(GLFWwindow* window);

	void Draw();

	void SetAnimator(MorphTargetAnimator& pAnimator);
};
