#pragma once
#include "Animator/morphTargetAnimator.hpp"

class Blender
{
	MorphTargetAnimator* animator = nullptr;

	std::vector<float> oldValues;

public:

	void Draw();

	void SetAnimator(MorphTargetAnimator& pAnimator);
};
