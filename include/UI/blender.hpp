#pragma once
#include "Animator/morphTargetAnimator.hpp"

class Blender
{
	MorphTargetAnimator* animator = nullptr;

public:

	void Draw() const;

	void SetAnimator(MorphTargetAnimator& pAnimator);
};
