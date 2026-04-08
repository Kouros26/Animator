#pragma once
#include "time.hpp"
#include "Rendering/OpenGL/renderer.hpp" // Renderer has to be included before window (because of glad.h)
#include "window.hpp"
#include "EngineObjects/gameObjectManager.hpp"
#include "Animator/morphTargetAnimator.hpp"
#include <Physics/physicsWorld.hpp>

class Application
{
	Window window{};

	GameObjectManager gameObjectManager{};

	Renderer renderer{ gameObjectManager.GetMainCamera() };
	PhysicsWorld physics{};

	Time time;

	MorphTargetAnimator* animator = nullptr;

public:

	Application();
	~Application();

	void Update();

	[[nodiscard]] bool ShouldClose() const;

private:

	void CreateObjects();
	void AddComponents();

	void ProcessInput(const double& deltaTime);
};
