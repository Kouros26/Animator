#include "Animator/morphTargetAnimator.hpp"

#include <filesystem>
#include <iostream>

MorphTargetAnimator::MorphTargetAnimator()
= default;

MorphTargetAnimator::MorphTargetAnimator(Model& defaultModel, const std::string& targetsFolderPath): model(&defaultModel)
{
	for (const auto& entry : std::filesystem::directory_iterator(PROJECT_PATH + targetsFolderPath))
	{
		targets.emplace_back(targetsFolderPath + entry.path().filename().string());
		values.emplace_back(0.0f);
	}
}

void MorphTargetAnimator::Update()
{
	
}

std::vector<float>& MorphTargetAnimator::GetValues()
{
	return values;
}
