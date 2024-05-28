#pragma once
#include <string>
#include <vector>
#include "EngineObjects/gameObject.hpp"

struct Targets
{
	std::string name;
	std::unordered_map<int, glm::vec3> displacement;

	Targets(const std::string& name, const std::unordered_map<int, glm::vec3>& target) : name(name), displacement(target){}
};

class MorphTargetAnimator
{
private:

	Model& model;

	Model defaultModel;
	std::vector<glm::vec3> defaultModelVertices;

	std::vector<Targets> targets;
	std::vector<float> values;

public:

	MorphTargetAnimator(Model& defaultModel);
	void Init(const std::string& targetsFolderPath);

	void Update(int targetIndex);

	std::vector<float>& GetValues();
	std::vector<Targets>& GetTargets();
};
