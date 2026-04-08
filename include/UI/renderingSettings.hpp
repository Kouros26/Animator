#pragma once
#include <Rendering/OpenGL/renderer.hpp>

class RenderingSettings
{
	Renderer* renderer = nullptr;

	bool wireframe = false;

public:

	void Draw();

	void SetRenderer(Renderer& pRenderer);
};