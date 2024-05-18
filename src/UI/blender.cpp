#include "UI/blender.hpp"

#include "imgui.h"

void Blender::Draw() const
{
	if (animator == nullptr)
		return;

	std::vector<float> values = animator->GetValues();
	ImGui::Begin("Face Blender");
	ImGui::SliderFloat("EyeBlink_L", &values[0], 0, 1);
	ImGui::End();
}

void Blender::SetAnimator(MorphTargetAnimator& pAnimator) 
{
	animator = &pAnimator;
}
