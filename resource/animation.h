#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

template<typename T>
class AnimationKey {
public:
    T value;
    float time;
};

typedef AnimationKey<glm::vec3> PositionKey;
typedef AnimationKey<glm::quat> RotationKey;

class AnimationNode {
public:
    std::string name;

    std::vector<PositionKey> positionkeys;
    std::vector<RotationKey> rotationKeys;


    glm::vec3 FindInterpolatedPosition(float time) const;
    glm::quat FindInterpolatedRotation(float time) const;
};

template<typename T>
int FindPosition(const std::vector<AnimationKey<T>>& keys, float time)
{
    for(int i = 0; i < keys.size() - 1; i++)
    {
        if(time < keys[i + 1].time)
        {
            return i;
        }
    }

    return 0;
}

template<typename T>
T InterpolateKey(const std::vector<AnimationKey<T>>& keys, float time)
{
    if(keys.size() == 1)
    {
        return keys[0].value;
    }

    int position = FindPosition(keys, time);
    int nextPosition = position + 1;
    float deltaTime = keys[nextPosition].time - keys[position].time;
    float factor = (time - keys[position].time) / deltaTime;

    T start = keys[position].value;
    T end = keys[nextPosition].value;
    return Interpolate(start, end, factor);

}

extern glm::vec3 Interpolate(const glm::vec3& start, const glm::vec3& end, float factor);
extern glm::quat Interpolate(const glm::quat& start, const glm::quat& end, float factor);


class Animation {
public:
    std::vector<AnimationNode> nodes;
    double tickPerSecond;
    double duration;

    const AnimationNode* FindNode(const std::string& name);
};