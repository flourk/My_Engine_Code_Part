#include "light.h"
#include "light_manager.h"

Light::Light()
{
    LightManager::AddLight(this);

    m_type = LightType::Directional;
    m_color = Vec4f(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::~Light()
{
    LightManager::RemoveLight(this);
}