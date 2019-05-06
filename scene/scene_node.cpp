#include "scene_node.h"
#include "camera.h"
#include <algorithm>
#include <glm/gtx/quaternion.hpp>

#include <iostream>
#include <core/log.h>


SceneNode::SceneNode()
{
    m_localPosition = glm::zero<Vec3f>();
    m_localRotation = glm::identity<Quat>();
    m_localScale = glm::one<Vec3f>();

    m_localMatrix = glm::identity<Mat4>();
    m_worldMatrix = glm::identity<Mat4>();

    m_isDirtyTransform = true;
    m_parent = nullptr;    
}

void SceneNode::SetParent(SceneNode* parent)
{
    if(m_parent == parent)
        return;

    if(!parent && parent->m_parent == this)
    {
        RemoveChild(parent);
        parent->m_parent = nullptr;
    }

    m_parent = parent;
    
    if(parent)
    {
        parent->AddChild(this);
    }

}

void SceneNode::AddChild(SceneNode* node)
{
    if(!node)
        return;

    m_children.push_back(node);
}
 
void SceneNode::RemoveChild(SceneNode* child)
{
    auto findIt = std::find(m_children.begin(), m_children.end(), child);
    if(findIt != m_children.end())
    {
        m_children.erase(findIt);
        (*findIt)->m_parent = nullptr;
    }
}

bool SceneNode::ContainChild(SceneNode* node)
{
    auto findIt = std::find(m_children.begin(), m_children.end(), node);
    return findIt != m_children.end();
}

SceneNode* SceneNode::FindNodeByName(const char* name)
{
    if(mName == name)
    {
        return this;
    }

    for(auto i = 0u; i < m_children.size(); i++)
    {
        auto find = m_children[i]->FindNodeByName(name);

        if(find != nullptr)
            return find;
    }

    return nullptr;
}


void SceneNode::Update()
{
    for(auto i = 0u; i < m_children.size(); i++)
    {
        m_children[i]->Update();
    } 
}

void SceneNode::Render(Camera* camera)
{
    for(auto i = 0u; i < m_children.size(); i++)
    {
        m_children[i]->Render(camera);
    }
}

const Mat4& SceneNode::GetWorldMatrix()
{
    if(m_isDirtyTransform)
    {
        m_worldMatrix = GetLocalMatrix();

        // logConsole << m_localMatrix;

        // for(SceneNode* prev = m_parent; prev; prev = prev->m_parent)
        // {
        //     m_worldMatrix = prev->GetWorldMatrix() * m_worldMatrix;
        // }
        if(m_parent)
        {
            m_worldMatrix = m_parent->GetWorldMatrix() * m_worldMatrix;
        }
    }
    return m_worldMatrix;
}


const Mat4& SceneNode::GetLocalMatrix()
{
    if(m_isDirtyTransform)
    {
        m_isDirtyTransform = false;
        UpdateLocalMatrix();
    }

    return m_localMatrix;
}

void SceneNode::UpdateLocalMatrix()
{
    // T * S * R * p
    // R和S都需要一个锚点，最后在进行T，否则锚点会改变。

    m_localMatrix = Mat4(1.0);
    m_localMatrix = glm::translate(m_localMatrix, m_localPosition);
    m_localMatrix = glm::scale(m_localMatrix, m_localScale);
    m_localMatrix *= glm::toMat4(m_localRotation);
}

void SceneNode::SetLocPosition(const Vec3f& value)
{
    MarkTransfromDirty();
    m_localPosition = value;
}

void SceneNode::SetLocRotation(const Quat& value)
{
    MarkTransfromDirty();
    m_localRotation = value;
}

void SceneNode::SetLocScale(const Vec3f& value)
{
    MarkTransfromDirty();
    m_localScale = value;
}


void SceneNode::Translate(const Vec3f& translate)
{
    MarkTransfromDirty();
    m_localPosition += translate;
}

void SceneNode::Rotate(float degree, const Vec3f& axis)
{
    MarkTransfromDirty();
    Quat q = glm::angleAxis(glm::radians(degree), axis);
    m_localRotation = glm::normalize(q * m_localRotation);
}

void SceneNode::Rotate(float x, float y, float z)
{
    MarkTransfromDirty();
	Quat qx = glm::angleAxis(x, Vec3f{1, 0, 0});
	Quat qy = glm::angleAxis(y, Vec3f{0, 1, 0});
	Quat qz = glm::angleAxis(z, Vec3f{0, 0, 1});

    m_localRotation = qz * qy * qx * m_localRotation;
}


void SceneNode::Scale(float x, float y, float z)
{
    Vec3f newScale = Vec3f(x * m_localScale.x, y * m_localScale.y, z * m_localScale.z);
    SetLocScale(newScale);
}


void SceneNode::MarkTransfromDirty()
{
    m_isDirtyTransform = true;
    for(auto i = 0; i < m_children.size(); i++)
    {
        m_children[i]->MarkTransfromDirty();
    }
}