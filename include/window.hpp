#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"

class Window
{
	GLFWwindow* window;

	int width = 800, height = 600;

public:

	Window();
	~Window();

	void SwapBuffers() const;
	void PollEvents() const;

	bool ShouldClose() const;
	inline static void FrameBufferResizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight);

	GLFWwindow* GetWindow() const;
};
