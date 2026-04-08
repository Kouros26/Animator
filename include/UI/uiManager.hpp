#pragma once
#include "blender.hpp"
#include "renderingSettings.hpp"
#include "GLFW/glfw3.h"

class UIManager
{
	Blender blender;
	RenderingSettings renderingSettings;

public:

	UIManager();
	UIManager(GLFWwindow* window);

	void Draw();

	void SetAnimator(MorphTargetAnimator& pAnimator);
	void SetRenderer(Renderer& pRendering);
};
