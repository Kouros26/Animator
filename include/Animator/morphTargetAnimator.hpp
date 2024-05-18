#pragma once
#include <string>
#include <vector>
#include <Resources/model.hpp>

class MorphTargetAnimator
{
private:

	Model* model;

	std::vector<Model> targets;
	std::vector<float> values;

public:

	MorphTargetAnimator();
	MorphTargetAnimator(Model& defaultModel, const std::string& targetsFolderPath);

	void Update();

	std::vector<float>& GetValues();
};
