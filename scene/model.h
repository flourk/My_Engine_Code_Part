#pragma once
#include "render/mesh.h"
#include "render/shader.h"
#include <vector>
#include "scene/scene_node.h"
#include "render/material.h"
#include <core/ptr.h>

class Model : public SceneNode {
public:
    void SetMaterial(Ref<Material> material)
    {
        m_material = material;
    }

    Ref<Material> GetMaterial()
    {
        return m_material;
    }

    void SetMeshes(const std::vector<Mesh*>& meshes);

    virtual void Render(Camera* camera) override;

protected:

    virtual void BindProperties(Camera* camera);

    std::vector<Mesh*> m_meshes;
    Ref<Material> m_material;
};