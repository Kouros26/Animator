#pragma once
#include "time.hpp"
#include "Rendering/OpenGL/renderer.hpp" // Renderer has to be included before window (because of glad.h)
#include "window.hpp"
#include "EngineObjects/gameObjectManager.hpp"
#include "Animator/morphTargetAnimator.hpp"

class Application
{
	Window window{};

	GameObjectManager gameObjectManager{};
	MorphTargetAnimator* animator;
	Renderer renderer{ gameObjectManager.GetMainCamera() };
	Time time;

	MorphTargetAnimator* animator {nullptr};

public:

	Application();
	~Application();
	void Test();

	void Update();

	[[nodiscard]] bool ShouldClose() const;

private:

	void ProcessInput(const double& deltaTime);
};
