#include "light_manager.h"
#include <algorithm>
#include <render/shader.h>
#include <render/material.h>
#include "light.h"

#include <core/log.h>

std::vector<Light*> LightManager::m_lights;

void LightManager::AddLight(Light* light)
{
    m_lights.push_back(light);
}

void LightManager::RemoveLight(Light* light)
{
    auto it = std::find(m_lights.begin(), m_lights.end(), light);
    if(it != m_lights.end())
    {
        m_lights.erase(it);
    }
}

void LightManager::SetupLight(Material* material)
{
    char buff[64] = {0};
    for(auto i = 0u; i < m_lights.size(); i++)
    {
        Light* light = m_lights[i];
        sprintf_s(buff, "lights[%d].color", i);
        material->SetVec4f(buff, light->GetColor());

        sprintf_s(buff, "lights[%d].pos", i);

        Vec3f forward = light->GetForward();
        Vec4f lightPos = Vec4f(-forward, 1.0);
        if(light->GetType() == LightType::Directional)
        {
            lightPos.w = 0.0;
        }
        material->SetVec4f(buff, lightPos);
        // logConsole << lightPos;
    }
}

