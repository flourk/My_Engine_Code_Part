#pragma once;

#include <glm/glm.hpp>
#include "scene_node.h"

class Camera : public SceneNode {
public:
    Camera();

    void SetPerspective(float fov, float aspect, float near, float far);
    const Mat4& GetPerspectiveMatrix()
    {
        return m_perspectiveMatrix;
    }

    const Mat4& GetViewMatrix();

protected:
    virtual void MarkTransfromDirty() override;

private:
    bool m_isCameraTransformDirty;

    Mat4 m_perspectiveMatrix;
    Mat4 m_viewMatrix;
};