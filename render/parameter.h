#pragma once

#include "core/types.h"
#include "texture.h"
#include <core/string_ex.h>

#include <map>
#include "pass.h"

#include "variant.h"

struct TextureSlot {
    String name;
    int num;
};

bool operator<(const TextureSlot& lhs, const TextureSlot& rhs);


class Parameter {
public:
    const float& GetFloat(const String& name) const;
    void SetFloat(const String& name, float value);

    const int& GetInt(const String& name) const;
    void SetInt(const String& name, int value);

    const Vec4f& GetVec4f(const String& name) const;
    void SetVec4f(const String& name, Vec4f value);

    const Mat4& GetMat4(const String& name) const;
    void SetMat4(const String& name,const Mat4& value);

    const Texture* GetTexture(const String& name, int slotNum) const;
    void SetTexture(const String& name, int slotNum, Texture* value);

    const std::map<String, Variant>& GetValueTable() const { return m_valueTable; }
    const std::map<TextureSlot, Texture*>& GetTextureTable() const { return m_textureTable; }

private:
    friend class Pass;

    std::map<String, Variant> m_valueTable;
    std::map<TextureSlot, Texture*> m_textureTable;
};