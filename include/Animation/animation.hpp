#pragma once
#include <map>
#include <string>
#include <vector>

#include "bone.hpp"
#include "boneInfo.hpp"
#include "glm/fwd.hpp"
#include "Resources/model.hpp"

struct AssimpNodeData
{
	glm::mat4 transform = glm::mat4(1.0f);
	std::string name;
	int childrenCount = 0;
	std::vector<AssimpNodeData> children;
};

class Animation
{
	float duration;
	int tickPerSecond;
	std::vector<Bone> bones;
	AssimpNodeData rootNode;
	std::map<std::string, BoneInfo> boneInfoMap;

public:

	Animation(const std::string& pPath, Model* model);

	Bone* FindBone(const std::string& name);

	[[nodiscard]] float GetTicksPerSecond() const;
	[[nodiscard]] float GetDuration() const;
	const AssimpNodeData& GetRootNode();
	const std::map<std::string, BoneInfo>& GetBoneIdMap();

private:

	void ReadMissingBones(const aiAnimation* animation, Model& model);
	void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);
};
