#pragma once
#include "model.h"
#include <resource/animation.h>


struct Bone {
    Bone()
    {
        finalMatrix = glm::mat4(1.0);
        offsetMatrix = glm::mat4(1.0);
    }

    std::string name{""};
    glm::mat4 offsetMatrix;
    glm::mat4 finalMatrix;
    
    int parentId;
};

struct Skeleton {
    std::vector<Bone> bones;
    std::vector<int> FindBoneChildren(std::string boneName);

    Bone* FindBone(const std::string& name);
    int FindBoneIndex(const std::string& name) const;
};

class SkinnedModel : public Model {
public:
    SkinnedModel() : m_animationTime(0)
    {

    }

    void ReadNodeHierarchy(float animationTime, Animation& animation, Skeleton& skeleton, Bone& bone, const glm::mat4& parentTransform);

    void SetSkeleton(const Skeleton& skeleton)
    {
        m_skeleton = skeleton;
    }

    void SetAnimation(const Animation& animation)
    {
        m_animation = animation;
    }

    virtual void Update() override;

protected:
    virtual void BindProperties(Camera* camera) override;

private:
    Skeleton m_skeleton;
    Animation m_animation;
    float m_animationTime;
};