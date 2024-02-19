#pragma once
#include "Renderer/OpenGL/renderer.hpp" // Renderer has to be included before window (because of glad.h)
#include "window.hpp"

class Application
{
	Window window;

	Renderer renderer;

public:

	Application();
	~Application();

	void Render();

	bool ShouldClose() const;

private:

	void ProcessInput();
};
