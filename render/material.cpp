#include "material.h"
#include "shader.h"

int Material::GetPassCount(int techIdx /* = 0 */)
{
    return m_shader->GetTechnique(techIdx)->GetPassCount();
}

void Material::SetInt(const String& name, int value)
{
    m_parameter.SetInt(name, value);
}

void Material::SetFloat(const String& name, float value)
{
    m_parameter.SetFloat(name, value);

}

void Material::SetVec4f(const String& name, const Vec4f& value)
{
    m_parameter.SetVec4f(name, value);
}

void Material::SetMat4(const String& name, const Mat4& value)
{
    m_parameter.SetMat4(name, value);
}

void Material::SetTexture(const String& name, int slotNum, Texture* value)
{
    m_parameter.SetTexture(name, slotNum, value);
}

Pass* Material::GetPass(int passIdx, int techIdx /* = 0 */)
{
    Technique* tech = m_shader->GetTechnique(techIdx);
    if(tech)
    {
        return tech->GetPass(passIdx);
    }
    return nullptr;
}




