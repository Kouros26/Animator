#include "UI/renderingSettings.hpp"

#include "imgui.h"

void RenderingSettings::Draw()
{
	ImGui::Begin("Rendering Settings");

	if (ImGui::Checkbox("Wireframe", &wireframe))
	{
		renderer->ToggleWireFrame();
	}

	ImGui::End();
}

void RenderingSettings::SetRenderer(Renderer& pRenderer)
{
	renderer = &pRenderer;
}
