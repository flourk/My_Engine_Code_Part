#include "model.h"
#include "camera.h"
#include "light_manager.h"

void Model::SetMeshes(const std::vector<Mesh*>& meshes)
{
    m_meshes = meshes;
}

void Model::BindProperties(Camera* camera)
{

    LightManager::SetupLight(m_material.get());

    const glm::mat4 model = GetWorldMatrix();
    m_material->SetMat4("model", model);

    const glm::mat4 view = camera->GetViewMatrix();
    m_material->SetMat4("view", view);

    const glm::mat4 project = camera->GetPerspectiveMatrix();
    m_material->SetMat4("project", project);

    // m_material->SetInt("diffuseTex", 0);
}


void Model::Render(Camera* camera)
{
    BindProperties(camera);

    int totalPass = m_material->GetPassCount();
    for(int i = 0; i < totalPass; i++)
    {
        Pass* pass = m_material->GetPass(i);
        gRenderer.SetPass(*pass, m_material->GetParameter());

        
        for(unsigned i = 0; i < m_meshes.size(); i++)
        {
            Mesh* mesh = m_meshes[i];
            mesh->Draw();
        }
    }

    SceneNode::Render(camera);
}