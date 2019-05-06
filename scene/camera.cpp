#include "camera.h"
#include <glm/ext.hpp>

Camera::Camera() :
    m_isCameraTransformDirty(true)
{

}

void Camera::SetPerspective(float fov, float aspect, float near, float far)
{
    m_perspectiveMatrix = glm::perspective(fov, aspect, near, far);
}

const glm::mat4& Camera::GetViewMatrix()
{
    if(m_isCameraTransformDirty)
    {
        m_isCameraTransformDirty = false;
        m_viewMatrix = glm::scale(Vec3f(1.0, 1.0, -1.0));

        Vec3f pos = m_localPosition;
        Quat rot = m_localRotation;

        for(auto node = GetParent() ; node; node = node->GetParent())
        {
            pos += node->GetLocPosition();
            rot = node->GetLocRotation() * rot;
        }

        m_viewMatrix *= glm::translate(Vec3f(-pos.x, -pos.y, -pos.z));
        m_viewMatrix *= glm::toMat4(glm::inverse(rot));
    }

    return m_viewMatrix;
}

void Camera::MarkTransfromDirty()
{
    m_isCameraTransformDirty = true;
    SceneNode::MarkTransfromDirty();
}

