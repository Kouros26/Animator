#include "Animation/animator.hpp"

Animator::Animator(Animation* animation)
{
    currentTime = 0.0;
    currentAnimation = animation;

    finalBoneMatrices.reserve(100);

    for (int i = 0; i < 100; i++)
        finalBoneMatrices.emplace_back(1.0f);
}

void Animator::UpdateAnimation(float deltaTime)
{
    if (currentAnimation)
    {
        currentTime += currentAnimation->GetTicksPerSecond() * deltaTime;
        currentTime = fmod(currentTime, currentAnimation->GetDuration());
        CalculateBoneTransform(&currentAnimation->GetRootNode(), glm::mat4(1.0f));
    }

    for (unsigned int i = 0; i < finalBoneMatrices.size(); i++)
    {
        std::string s = "finalBonesMatrices[" + std::to_string(i) + "]";
        /*Application::GetMainShader().SetMat4(finalBoneMatrices[i], s.c_str());*/
    }
}

void Animator::PlayAnimation(Animation& animation)
{
    currentAnimation = &animation;
    currentTime = 0.0f;
}

void Animator::CalculateBoneTransform(const AssimpNodeData* node, const glm::mat4& parentTransform)
{
	const std::string nodeName = node->name;
    glm::mat4 nodeTransform = node->transform;

    if (Bone* Bone = currentAnimation->FindBone(nodeName))
    {
        Bone->Update(currentTime);
        nodeTransform = Bone->GetLocalTransform();
    }

    const glm::mat4 globalTransformation = parentTransform * nodeTransform;

    auto boneInfoMap = currentAnimation->GetBoneIdMap();
    if (boneInfoMap.contains(nodeName))
    {
	    const int index = boneInfoMap[nodeName].id;
	    const glm::mat4 offset = boneInfoMap[nodeName].offset;
        finalBoneMatrices[index] = globalTransformation * offset;
    }

    for (int i = 0; i < node->childrenCount; i++)
        CalculateBoneTransform(&node->children[i], globalTransformation);
}

std::vector<glm::mat4> Animator::GetFinalBoneMatrices()
{
    return finalBoneMatrices;
}
