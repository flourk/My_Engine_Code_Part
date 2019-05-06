#pragma once

#include <resource/resource.h>
#include <core/string_ex.h>
#include <core/types.h>
#include "shader.h"
#include "parameter.h"

class Pass;

class Material : public Resource {
public:
    void SetShader(Shader* shader)
    {
        m_shader = shader;
    }

    Shader* GetShader()
    {
        return m_shader;
    }

    void SetInt(const String& name, int value);

    void SetFloat(const String& name, float value);

    void SetVec4f(const String& name, const Vec4f& value);

    void SetMat4(const String& name, const Mat4& value);
    
    void SetTexture(const String& name, int slotNum, Texture* value);
    
    int GetPassCount(int techIdx = 0);

    Pass* GetPass(int passIdx, int techIdx = 0);

    const Parameter& GetParameter() const { return m_parameter; }

private:
    Shader* m_shader;
    Parameter m_parameter;
};