#include "Animator/morphTargetAnimator.hpp"

#include <filesystem>
#include "glm/gtx/compatibility.hpp"

MorphTargetAnimator::MorphTargetAnimator(Model& defaultModel) : model(defaultModel), defaultModel(model)
{
	for (const auto& vertice : defaultModel.GetMeshes()[0].GetVertices())
	{
		defaultModelVertices.push_back(vertice.Position);
	}
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
				affectedVertices.insert(std::make_pair(i, temporaryModel.GetMeshes()[0].GetVertices()[i].Position - defaultModel.GetMeshes()[0].GetVertices()[i].Position));
			}
		}

		targets.emplace_back(entry.path().filename().string(), affectedVertices);
		values.emplace_back(0.0f);
	}
}

void MorphTargetAnimator::Update(float oldValue, int targetIndex, bool incrementing)
{
	Mesh& mesh = model.GetMeshes()[0];
	std::vector<Vertex>& vertices = mesh.GetVertices();

	for (int j = 0; j < targets[targetIndex].displacement.size(); j++)
	{
		if (incrementing)
		{
			glm::vec3 displacementLerp = lerp(glm::vec3{ 0 }, targets[targetIndex].displacement[j], values[targetIndex])
				- lerp(glm::vec3{ 0 }, targets[targetIndex].displacement[j], oldValue);

			vertices[j].Position += displacementLerp;
		}

		else
		{
			glm::vec3 displacementLerp = lerp(targets[targetIndex].displacement[j], glm::vec3{0}, values[targetIndex])
				- lerp(targets[targetIndex].displacement[j], glm::vec3{ 0 }, oldValue);

			vertices[j].Position -= displacementLerp;
		}
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
