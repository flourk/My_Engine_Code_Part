#pragma once

#include <GL/glew.h>
#include <string>
#include <core/string_ex.h>
#include <map>
#include <core/types.h>
#include <shader_parser/shader_compiler.h>

#include "technique.h"
#include <vector>

class Shader {
public:
    Shader() {} ;

    void AddTechnique(Technique* tech);

    int GetTechniqueCount() const { return m_techniques.size(); }

    Technique* GetTechnique(int idx) const;

private:
    std::vector<Technique*> m_techniques;
};