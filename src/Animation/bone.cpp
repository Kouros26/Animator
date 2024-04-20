#include "Animation/bone.hpp"

#define GLM_ENABLE_EXPERIMENTAL 1

#include "glm/gtx/quaternion.hpp"

Bone::Bone(const std::string& name, int id, const aiNodeAnim* channel)
    : id(id), name(name), localTransform(1.0f)
{
    positionCount = channel->mNumPositionKeys;

    for (int positionIndex = 0; positionIndex < positionCount; ++positionIndex)
    {
        aiVector3D aiPosition = channel->mPositionKeys[positionIndex].mValue;
        float timeStamp = channel->mPositionKeys[positionIndex].mTime;
        KeyPosition data;
        data.position = AssimpGLMHelpers::GetGLMVec(aiPosition);
        data.timeStamp = timeStamp;
        positions.push_back(data);
    }

    rotationCount = channel->mNumRotationKeys;
    for (int rotationIndex = 0; rotationIndex < rotationCount; ++rotationIndex)
    {
        aiQuaternion aiOrientation = channel->mRotationKeys[rotationIndex].mValue;
        float timeStamp = channel->mRotationKeys[rotationIndex].mTime;
        KeyRotation data;
        data.orientation = AssimpGLMHelpers::GetGLMQuat(aiOrientation);
        data.timeStamp = timeStamp;
        rotations.push_back(data);
    }

    scaleCount = channel->mNumScalingKeys;
    for (int keyIndex = 0; keyIndex < scaleCount; ++keyIndex)
    {
        aiVector3D scale = channel->mScalingKeys[keyIndex].mValue;
        float timeStamp = channel->mScalingKeys[keyIndex].mTime;
        KeyScale data;
        data.scale = AssimpGLMHelpers::GetGLMVec(scale);
        data.timeStamp = timeStamp;
        scales.push_back(data);
    }
}

void Bone::Update(float animationTime)
{
	const glm::mat4 translation = InterpolatePosition(animationTime);
	const glm::mat4 rotation = InterpolateRotation(animationTime);
	const glm::mat4 scale = InterpolateScaling(animationTime);
    localTransform = translation * rotation * scale;
}

glm::mat4 Bone::GetLocalTransform() const
{
    return localTransform;
}

std::string Bone::GetBoneName() const
{
    return name;
}

int Bone::GetBoneId() const
{
    return id;
}

int Bone::GetPositionIndex(float animationTime) const
{
    for (int index = 0; index < positionCount - 1; ++index)
    {
        if (animationTime < positions[index + 1].timeStamp)
            return index;
    }

    return -1;
}

int Bone::GetRotationIndex(float animationTime) const
{
    for (int index = 0; index < rotationCount - 1; ++index)
    {
        if (animationTime < rotations[index + 1].timeStamp)
            return index;
    }

    return -1;
}

int Bone::GetScaleIndex(float animationTime) const
{
    for (int index = 0; index < scaleCount - 1; ++index)
    {
        if (animationTime < scales[index + 1].timeStamp)
            return index;
    }

    return -1;
}

float Bone::GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime)
{
	const float midWayLength = animationTime - lastTimeStamp;
    const float framesDiff = nextTimeStamp - lastTimeStamp;
	const float scaleFactor = midWayLength / framesDiff;
    return scaleFactor;
}

glm::mat4 Bone::InterpolatePosition(float animationTime)
{
    if (positionCount == 1)
        return glm::translate(glm::mat4(1.0f), positions[0].position);

    const int p0Index = GetPositionIndex(animationTime);
    const int p1Index = p0Index + 1;
    const float scaleFactor = GetScaleFactor(positions[p0Index].timeStamp,
                                             positions[p1Index].timeStamp, animationTime);
    const glm::vec3 finalPosition = glm::mix(positions[p0Index].position,
                                             positions[p1Index].position, scaleFactor);
    return translate(glm::mat4(1.0f), finalPosition);
}

glm::mat4 Bone::InterpolateRotation(float animationTime)
{
    if (positionCount == 1)
    {
	    const auto rotation = glm::normalize(rotations[0].orientation);
        return glm::toMat4(rotation);
    }

    const int p0Index = GetRotationIndex(animationTime);
    const int p1Index = p0Index + 1;
    const float scaleFactor = GetScaleFactor(rotations[p0Index].timeStamp,
                                             rotations[p1Index].timeStamp, animationTime);
    glm::quat finalRotation = glm::slerp(rotations[p0Index].orientation,
        rotations[p1Index].orientation, scaleFactor);
    finalRotation = glm::normalize(finalRotation);
    return glm::toMat4(finalRotation);
}

glm::mat4 Bone::InterpolateScaling(float animationTime)
{
    if (scaleCount == 1)
        return glm::scale(glm::mat4(1.0f), scales[0].scale);

    const int p0Index = GetScaleIndex(animationTime);
    const int p1Index = p0Index + 1;
    const float scaleFactor = GetScaleFactor(scales[p0Index].timeStamp,
                                             scales[p1Index].timeStamp, animationTime);
    const glm::vec3 finalScale = glm::mix(scales[p0Index].scale, scales[p1Index].scale
                                          , scaleFactor);
    return glm::scale(glm::mat4(1.0f), finalScale);
}
