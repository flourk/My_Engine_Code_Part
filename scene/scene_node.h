#pragma once

#include <vector>

#include <core/types.h>
#include <core/timer.h>

#include "render/renderer.h"

class Camera;

class SceneNode {
public:
    SceneNode();

    SceneNode* FindNodeByName(const char* name);

    void SetParent(SceneNode* parent);
    SceneNode* GetParent() { return m_parent; }

    bool ContainChild(SceneNode* child);

    virtual void Update();
    virtual void Render(Camera* camera);


    const std::vector<SceneNode*>& GetChildren()
    {
        return m_children;
    }


    void Translate(const Vec3f& translate);
    
    void Rotate(float degree, const Vec3f& axis);
    void Rotate(float x, float y, float z);

    void Scale(float x, float y, float z);

    const glm::mat4& GetLocalMatrix();
    const glm::mat4& GetWorldMatrix();

    void SetLocPosition(const Vec3f& value);
    inline void SetLocPosition(float x, float y, float z)
    {
        SetLocPosition(Vec3f(x, y, z));
    }

    void SetLocRotation(const Quat& value);
    void SetLocScale(const Vec3f& value);

    inline Vec3f GetForward()
    {
        return Mat3(GetWorldMatrix()) * Vec3f(0, 0, 1);
    } 


    Vec3f GetLocPosition()
    {
        return m_localPosition;
    }

    Vec3f GetEulerAngles()
    {
        return  glm::eulerAngles(m_localRotation);
    }

    Quat GetLocRotation()
    {
        return m_localRotation;
    }

    Vec3f GetLocScale()
    {
        return m_localScale;
    }

    std::string mName;

    template<typename T>
    T* As()
    {
        return (T*)this;
    }


protected:
    void AddChild(SceneNode* child);
    void RemoveChild(SceneNode* child);

    void UpdateLocalMatrix();

    virtual void MarkTransfromDirty();

protected:

    bool m_isDirtyTransform;

    Vec3f m_localPosition;
    Quat m_localRotation;
    Vec3f m_localScale;

private:
    Mat4 m_localMatrix;
    Mat4 m_worldMatrix;

    SceneNode* m_parent;
    std::vector<SceneNode*> m_children;
};