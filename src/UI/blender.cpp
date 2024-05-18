#include "UI/blender.hpp"

#include "imgui.h"

void Blender::Draw() const
{
	if (animator == nullptr)
		return;

	std::vector<float>& values = animator->GetValues();
	const std::vector<Targets>& targets = animator->GetTargets();

	ImGui::Begin("Face Blender");

	for (int i = 0; i < targets.size(); i++)
	{
		ImGui::SliderFloat(targets[i].name.c_str(), &values[i], 0.0f, 1.0f);
	}

	ImGui::End();
}

void Blender::SetAnimator(MorphTargetAnimator& pAnimator) 
{
	animator = &pAnimator;
}
