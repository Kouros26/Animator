#include "window.hpp"

#include <iostream>

void Window::SwapBuffers() const
{
	glfwSwapBuffers(window);
}

void Window::PollEvents() const
{
	glfwPollEvents();
}

bool Window::ShouldClose() const
{
	return glfwWindowShouldClose(window);
}

void Window::FrameBufferResizeCallback(GLFWwindow* pWindow, int pWidth, int pHeight)
{
	glViewport(0, 0, pWidth, pHeight);
}

Window::Window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "LearnOpenGL", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, FrameBufferResizeCallback);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
}

Window::~Window()
{
	glfwTerminate();
}

void Window::ProcessInput() const
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
