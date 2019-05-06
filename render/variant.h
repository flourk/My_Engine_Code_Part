#pragma once

#include <core/types.h>
#include "texture.h"

class Variant {
public:
    enum Type {
        VT_Float,
        VT_Int,
        VT_Vec4f,
        VT_Mat4,
    };

    template<typename T>
    static const T& GetDefaultValue()
    {
        return NULL;
    }


    Variant(float value)
    {
        SetValue(value);
    }

    Variant(int value)
    {
        SetValue(value);
    }

    Variant(const Vec4f& value)
    {
        SetValue(value);
    }

    Variant(const Mat4& value)
    {
        SetValue(value);
    }

    const int& GetInt() const;

    const float& GetFloat() const;

    const Vec4f& GetVec4f() const;
    
    const Mat4& GetMat4() const;

    Type GetType() const { return m_type; }

private:
    void SetValue(float value)
    {
        m_type = VT_Float;
        m_data.f = value;
    }

    void SetValue(int value)
    {
        m_type = VT_Int;
        m_data.i = value;
    }

    void SetValue(const Vec4f& value)
    {
        m_type = VT_Vec4f;
        m_data.vec4f = value;
    }

    void SetValue(const Mat4& value)
    {
        m_type = VT_Mat4;
        m_data.mat4 = value;
    }



private:
    union Data
    {
        float f;
        int i;
        Vec4f vec4f;
        Mat4 mat4;
    };

    Data m_data;
    Type m_type;

};

template<>
const int& Variant::GetDefaultValue<int>();


template<>
const float& Variant::GetDefaultValue<float>();

template<>
const Vec4f& Variant::GetDefaultValue<Vec4f>();


template<>
const Mat4& Variant::GetDefaultValue<Mat4>();