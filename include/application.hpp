#pragma once
#include "Renderer/OpenGL/renderer.hpp" // Renderer has to be included before window (because of glad.h)
#include "window.hpp"
#include "EngineObjects/gameObjectManager.hpp"

class Application
{
	Window window;

	Renderer renderer;

	GameObjectManager gameObjectManager;

public:

	Application();
	~Application();

	void Render();

	[[nodiscard]] bool ShouldClose() const;

private:

	void ProcessInput();
};
