#include "variant.h"


const int& Variant::GetInt() const
{
    if(m_type == VT_Int)
    {
        return m_data.i;
    }

    return Variant::GetDefaultValue<int>();
}

const float& Variant::GetFloat() const
{
    if(m_type == VT_Float)
    {
        return m_data.f;
    }

    return Variant::GetDefaultValue<float>();
}

const Vec4f& Variant::GetVec4f() const
{
    if(m_type == VT_Vec4f)
    {
        return m_data.vec4f;
    }

    return Variant::GetDefaultValue<Vec4f>();
}

const Mat4& Variant::GetMat4() const
{
    static const Mat4 defaultValue  = glm::identity<Mat4>();
    if(m_type == VT_Mat4)
    {
        return m_data.mat4;
    }

    return Variant::GetDefaultValue<Mat4>();
}

template<>
const int& Variant::GetDefaultValue<int>()
{
    static const int defaultValue  = 0;
    return defaultValue;
}

template<>
const float& Variant::GetDefaultValue<float>()
{
    static const float defaultValue  = 0.0;
    return defaultValue;
}

template<>
const Vec4f& Variant::GetDefaultValue<Vec4f>()
{
    static const Vec4f defaultValue  = Vec4f(0.0, 0.0, 0.0, 0.0);
    return defaultValue;
}

template<>
inline const Mat4& Variant::GetDefaultValue<Mat4>()
{
    static const Mat4 defaultValue  = glm::identity<Mat4>();
    return defaultValue;
}