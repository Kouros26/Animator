#include "Animation/animation.hpp"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"

Animation::Animation(const std::string& pPath, Model* model)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(pPath, aiProcess_Triangulate);
    assert(scene && scene->mRootNode);
    const auto animation = scene->mAnimations[0];
    duration = animation->mDuration;
    tickPerSecond = animation->mTicksPerSecond;
    ReadHierarchyData(rootNode, scene->mRootNode);
    ReadMissingBones(animation, *model);
}

Bone* Animation::FindBone(const std::string& name)
{
	if (const auto iterator = std::ranges::find_if(bones,
	                                               [&](const Bone& Bone)
	                                               {
		                                               return Bone.GetBoneName() == name;
	                                               }
	); iterator == bones.end())
        return nullptr;

    else 
        return &(*iterator);
}

float Animation::GetTicksPerSecond() const
{
    return tickPerSecond;
}

float Animation::GetDuration() const
{
    return duration;
}

const AssimpNodeData& Animation::GetRootNode()
{
    return rootNode;
}

const std::map<std::string, BoneInfo>& Animation::GetBoneIdMap()
{
    return boneInfoMap;
}

void Animation::ReadMissingBones(const aiAnimation* animation, Model& model)
{
	const int size = animation->mNumChannels;

    auto& boneInfoMap = model.GetBoneInfoMap();//getting boneInfoMap from Model class
    int& boneCount = model.GetBoneCount(); //getting the m_BoneCounter from Model class

    //reading channels(bones engaged in an animation and their keyframes)
    for (int i = 0; i < size; i++)
    {
        auto channel = animation->mChannels[i];
        std::string boneName = channel->mNodeName.data;

        if (!boneInfoMap.contains(boneName))
        {
            boneInfoMap[boneName].id = boneCount;
            boneCount++;
        }
        bones.emplace_back(channel->mNodeName.data,
                             boneInfoMap[channel->mNodeName.data].id, channel);
    }

    boneInfoMap = boneInfoMap;
}

void Animation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
{
    assert(src);

    dest.name = src->mName.data;
    dest.transform = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
    dest.childrenCount = src->mNumChildren;

    for (int i = 0; i < src->mNumChildren; i++)
    {
        AssimpNodeData newData;
        ReadHierarchyData(newData, src->mChildren[i]);
        dest.children.push_back(newData);
    }
}
