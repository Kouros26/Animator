#pragma once
#include <glad/glad.h>
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>

class Window
{
	GLFWwindow* window;

	int width = 800, height = 600;

	constexpr void SetWindowSize(int pWidth, int pHeight);

public:

	Window();
	~Window();

	void SwapBuffers() const;
	void PollEvents() const;

	void ToggleVSync(const bool value);
	[[nodiscard]] bool ShouldClose() const;


	inline static void FrameBufferResizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight);

	[[nodiscard]] GLFWwindow* GetWindow() const;
	[[nodiscard]] constexpr glm::vec2 GetWindowSize() const;
};

constexpr void Window::SetWindowSize(int pWidth, int pHeight)
{
	width = pWidth;
	height = pHeight;
}
