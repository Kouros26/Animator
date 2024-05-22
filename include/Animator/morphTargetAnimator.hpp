#pragma once
#include <string>
#include <vector>
#include "EngineObjects/gameObject.hpp"

struct Targets
{
	std::string name;
	std::unordered_map<int, glm::vec3> target;

	Targets(const std::string& name, const std::unordered_map<int, glm::vec3>& target) : name(name), target(target){}
};

class MorphTargetAnimator
{
private:

	Model& model;

	Model defaultModel;
	std::vector<Vertex> defaultModelVertices;

	std::vector<Targets> targets;
	std::vector<float> values;

public:

	MorphTargetAnimator(Model& defaultModel);
	void Init(const std::string& targetsFolderPath);

	void Update();

	std::vector<float>& GetValues();
	std::vector<Targets>& GetTargets();
};
