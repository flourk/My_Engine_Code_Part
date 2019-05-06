#include "animation.h"
#include <algorithm>


glm::vec3 Interpolate(const glm::vec3& start, const glm::vec3& end, float factor)
{
    return glm::lerp(start, end, factor);
}
glm::quat Interpolate(const glm::quat& start, const glm::quat& end, float factor)
{
    return glm::slerp(start, end, factor);
}


glm::vec3 AnimationNode::FindInterpolatedPosition(float time) const
{
    return InterpolateKey(positionkeys, time);
}

glm::quat AnimationNode::FindInterpolatedRotation(float time) const
{
    return InterpolateKey(rotationKeys, time);
}

const AnimationNode* Animation::FindNode(const std::string& name)
{
    for(unsigned i = 0; i < nodes.size(); i++)
    {
        if(nodes[i].name == name)
            return &nodes[i];
    }

    return nullptr;
}
