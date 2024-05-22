#include "Animator/morphTargetAnimator.hpp"

#include <filesystem>
#include "glm/gtx/compatibility.hpp"

MorphTargetAnimator::MorphTargetAnimator(Model& defaultModel) : model(defaultModel), defaultModel(model)
{
	defaultModelVertices = defaultModel.GetMeshes()[0].GetVertices();
}

void MorphTargetAnimator::Init(const std::string& targetsFolderPath)
{
	for (const auto& entry : std::filesystem::directory_iterator(PROJECT_PATH + targetsFolderPath))
	{
		Model temporaryModel(targetsFolderPath + entry.path().filename().string());
		std::unordered_map<int, glm::vec3> affectedVertices;

		for (int i = 0; i < temporaryModel.GetMeshes()[0].GetVertices().size(); i++)
		{
			if (temporaryModel.GetMeshes()[0].GetVertices()[i].Position != defaultModel.GetMeshes()[0].GetVertices()[i].Position)
			{
				affectedVertices.insert(std::make_pair(i, temporaryModel.GetMeshes()[0].GetVertices()[i].Position));
			}
		}

		targets.emplace_back(entry.path().filename().string(), affectedVertices);
		values.emplace_back(0.0f);
	}
}

void MorphTargetAnimator::Update()
{
	Mesh& mesh = model.GetMeshes()[0];
	std::vector<Vertex>& vertices = mesh.GetVertices();

	for (int i = 0; i < targets.size(); i++)
	{
		if (values[i] == 0.0f)
			continue;

		//std::vector<Vertex>& targetVertices = targets[i].target.GetMeshes()[0].GetVertices();

		for (int j = 0; j < targets[i].target.size(); j++)
		{
			vertices[j].Position = lerp(defaultModelVertices[j].Position, targets[i].target[j], values[i]);
		}

		//for (int j = 0; j < vertices.size(); j++)
		//{
		//	vertices[j].Position = lerp(defaultModelVertices[j].Position, targetVertices[j].Position, values[i]);
		//}
	}
}

std::vector<float>& MorphTargetAnimator::GetValues()
{
	return values;
}

std::vector<Targets>& MorphTargetAnimator::GetTargets()
{
	return targets;
}
