#include "parameter.h"

bool operator<(const TextureSlot& lhs, const TextureSlot& rhs)
{
        if(lhs.name == rhs.name)
        {
            return lhs.num < rhs.num;
        }

        return lhs.name < rhs.name;
}


const float& Parameter::GetFloat(const String& name) const
{
    auto it = m_valueTable.find(name);
    if(it != m_valueTable.end())
    {
        return it->second.GetFloat();
    }

    return Variant::GetDefaultValue<float>();
}

void Parameter::SetFloat(const String& name, float value)
{
    auto it = m_valueTable.find(name);
    if(it == m_valueTable.end())
    {
        m_valueTable.insert(std::make_pair(name, Variant(value)));
    }
    else
    {
        it->second = value;
    }
}

const int& Parameter::GetInt(const String& name) const
{
    auto it = m_valueTable.find(name);
    if(it != m_valueTable.end())
    {
        return it->second.GetInt();
    }

    return Variant::GetDefaultValue<int>();
}

void Parameter::SetInt(const String& name, int value)
{
    auto it = m_valueTable.find(name);
    if(it == m_valueTable.end())
    {
        m_valueTable.insert(std::make_pair(name, Variant(value)));
    }
    else
    {
        it->second = value;
    }
}

const Vec4f& Parameter::GetVec4f(const String& name) const
{
    auto it = m_valueTable.find(name);
    if(it != m_valueTable.end())
    {
        return it->second.GetVec4f();
    }

    return Variant::GetDefaultValue<Vec4f>();
}

void Parameter::SetVec4f(const String& name, Vec4f value)
{
    auto it = m_valueTable.find(name);
    if(it == m_valueTable.end())
    {
        m_valueTable.insert(std::make_pair(name, Variant(value)));
    }
    else
    {
        it->second = value;
    }
}

const Mat4& Parameter::GetMat4(const String& name) const
{
    auto it = m_valueTable.find(name);
    if(it != m_valueTable.end())
    {
        return it->second.GetMat4();
    }

    return Variant::GetDefaultValue<Mat4>();
}

void Parameter::SetMat4(const String& name, const Mat4& value)
{
    auto it = m_valueTable.find(name);
    if(it == m_valueTable.end())
    {
        m_valueTable.insert(std::make_pair(name, Variant(value)));
    }
    else
    {
        it->second = value;
    }
}

const Texture* Parameter::GetTexture(const String& name, int slotNum) const
{
    TextureSlot slot = { name, slotNum };
    auto it = m_textureTable.find(slot);
    if(it != m_textureTable.end())
    {
        return it->second;
    }

    return nullptr;
}
  
void Parameter::SetTexture(const String& name, int slotNum, Texture* value)
{
    TextureSlot slot = { name, slotNum };
        auto it = m_textureTable.find(slot);
    if(it != m_textureTable.end())
    {
        it->second = value;
    }

    m_textureTable.insert(std::make_pair(slot, value));
}

