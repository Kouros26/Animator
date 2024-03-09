#pragma once
#include "time.hpp"
#include "Rendering/OpenGL/renderer.hpp" // Renderer has to be included before window (because of glad.h)
#include "window.hpp"
#include "EngineObjects/gameObjectManager.hpp"
#include "Resources/resourceManager.hpp"

class Application
{
	Window window{};

	GameObjectManager gameObjectManager{};

	Renderer renderer{ gameObjectManager.GetMainCamera() };
	Time time;

public:

	Application();
	~Application();

	void Update();

	[[nodiscard]] bool ShouldClose() const;

private:

	void ProcessInput(const double& deltaTime);
};
