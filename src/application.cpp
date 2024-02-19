#include "application.hpp"

Application::Application()
{
}

Application::~Application()
{

}

void Application::Render()
{
	ProcessInput();

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	renderer.Render();

	window.SwapBuffers();
	window.PollEvents();
}

bool Application::ShouldClose() const
{
	return window.ShouldClose();
}

void Application::ProcessInput()
{
	GLFWwindow* windowRef = window.GetWindow();

	if (glfwGetKey(windowRef, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(windowRef, true);

	if (glfwGetKey(windowRef, GLFW_KEY_MINUS) == GLFW_PRESS)
		renderer.ToggleWireFrame();
}