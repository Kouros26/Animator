#include "application.hpp"

Application::Application()
{
}

Application::~Application()
{

}

void Application::Render() const
{
	window.ProcessInput();

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
