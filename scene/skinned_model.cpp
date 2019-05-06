#include "skinned_model.h"
#include "camera.h"

#include <iostream>
#include <core/log.h>

using namespace std;

std::vector<int> Skeleton::FindBoneChildren(std::string boneName)
{
    std::vector<int> ret;

    for(unsigned i = 0; i < bones.size(); i++)
    {
        if(bones[i].parentId == -1)
            continue;

        Bone& curBone = bones[i];
        Bone& parentBone = bones[curBone.parentId];

        if(parentBone.name == boneName)
        {
            ret.push_back(i);
        }
    }

    return ret;
}


Bone* Skeleton::FindBone(const std::string& name)
{
    for(unsigned i = 0; i < bones.size(); i++)
    {
        if(bones[i].name == name)
            return &bones[i];
    }

    return nullptr;
}

int Skeleton::FindBoneIndex(const std::string& name) const
{
    for(unsigned i = 0; i < bones.size(); i++)
    {
        if(bones[i].name == name)
            return i;
    }

    return 0;
}

void SkinnedModel::BindProperties(Camera* camera)
{
    Model::BindProperties(camera);

    char buf[16] = {0};
    for(unsigned i = 0; i <m_skeleton.bones.size(); i++)
    {
        sprintf_s(buf, "bones[%d]", i);
        m_material->SetMat4(buf, m_skeleton.bones[i].finalMatrix);
    }

        // Mesh* pMesh = m_meshes[0];
    // Vertex& vertex = pMesh->m_vertex[0];

    // glm::mat4 mat(0.0);

    // for(int i = 0; i < 4; i++)
    // {
    //     Bone& bone = m_skeleton.bones[vertex.boneIndices[i]];
    //     float weight = vertex.boneWeights[i];
    //     mat += bone.finalMatrix * weight;
    // }

    // glm::vec4 value = project * model * mat * glm::vec4(vertex.position, 1.0);
    // logConsole << (value);
}


void SkinnedModel::Update()
{
    m_animationTime = (float)fmod(m_animationTime + Timer::GetDeltaTime() * m_animation.tickPerSecond, m_animation.duration);
    ReadNodeHierarchy(m_animationTime, m_animation, m_skeleton, m_skeleton.bones[0], glm::mat4(1.0));
}



void SkinnedModel::ReadNodeHierarchy(float animationTime, Animation& animation, 
    Skeleton& skeleton, Bone& bone, const glm::mat4& parentTransform)
{
    std::string boneName = bone.name;
    
    glm::mat4 nodeMatrix = glm::mat4(1.0);

    const AnimationNode* pAnimNode = animation.FindNode(boneName);


    if(pAnimNode)
    {
        // cout << boneName << endl;

        glm::vec3 newPosition = pAnimNode->FindInterpolatedPosition(animationTime);
        glm::quat newRotation = pAnimNode->FindInterpolatedRotation(animationTime);

        // std::cout << animationTime << std::endl;
        // glm::vec3 euler = glm::eulerAngles(newRotation);

        if(boneName == "astroBoy_newSkeleton_root")
        {
            // logConsole << glm::vec4(newPosition, 1.0);
            // logConsole << newRotation;
        }

        glm::mat4x4 rotMatrix = glm::toMat4(newRotation);
        glm::mat4x4 posMatrix = glm::translate(newPosition);
        nodeMatrix = posMatrix * rotMatrix;
    }



    glm::mat4x4 globalTransformation = parentTransform * nodeMatrix;
    bone.finalMatrix = globalTransformation * bone.offsetMatrix;


    std::vector<int> children = skeleton.FindBoneChildren(bone.name);

    for(unsigned i = 0; i < children.size(); i++)
    {
        Bone& bone = skeleton.bones[children[i]];
        ReadNodeHierarchy(animationTime, animation, skeleton, bone, globalTransformation);
    }
}