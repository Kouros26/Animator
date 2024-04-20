#pragma once
#include <string>

#include "assimp/anim.h"
#include "glm/fwd.hpp"
#include "glm/vec3.hpp"

#include "AssimpGLMHelper.hpp"

struct KeyPosition
{
    glm::vec3 position;
    float timeStamp;
};

struct KeyRotation
{
    glm::quat orientation;
    float timeStamp;
};

struct KeyScale
{
    glm::vec3 scale;
    float timeStamp;
};

class Bone
{
private:

    int id;
    std::string name;

    std::vector<KeyPosition> positions;
    std::vector<KeyRotation> rotations;
    std::vector<KeyScale> scales;

    unsigned positionCount;
    unsigned rotationCount;
    unsigned scaleCount;

    glm::mat4 localTransform;

public:

    Bone(const std::string& name, int id, const aiNodeAnim* channel);

    void Update(float animationTime);

    [[nodiscard]] glm::mat4 GetLocalTransform() const;
    [[nodiscard]] std::string GetBoneName() const;
    [[nodiscard]] int GetBoneId() const;

    [[nodiscard]] int GetPositionIndex(float animationTime) const;
    [[nodiscard]] int GetRotationIndex(float animationTime) const;
    [[nodiscard]] int GetScaleIndex(float animationTime) const;

private:

    float GetScaleFactor(float lastTimeStamp, float nextTimeStamp, float animationTime);

    glm::mat4 InterpolatePosition(float animationTime);
    glm::mat4 InterpolateRotation(float animationTime);
    glm::mat4 InterpolateScaling(float animationTime);
};