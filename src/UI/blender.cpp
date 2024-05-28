#include "UI/blender.hpp"

#include "imgui.h"

void Blender::Draw()
{
	if (animator == nullptr)
		return;

	std::vector<float>& values = animator->GetValues();
	const std::vector<Targets>& targets = animator->GetTargets();

	ImGui::Begin("Face Blender");

	for (int i = 0; i < targets.size(); i++)
	{
		if (ImGui::SliderFloat(targets[i].name.c_str(), &values[i], 0.0f, 1.0f))
		{
			animator->Update(oldValues[i], i, values[i] > oldValues[i]);
		}
	}

	ImGui::End();

	oldValues = values;
}

void Blender::SetAnimator(MorphTargetAnimator& pAnimator) 
{
	animator = &pAnimator;
	oldValues.reserve(animator->GetTargets().size());
}
