#include "shader.h"
#include <fstream>
#include <sstream>

#include <iostream>
#include <core/log.h>

using namespace std;

void Shader::AddTechnique(Technique* tech)
{
    auto it = std::find(m_techniques.begin(), m_techniques.end(), tech);

    if(it == m_techniques.end())
    {
        m_techniques.push_back(tech);
    }
}

Technique* Shader::GetTechnique(int idx) const
{
    if(idx < 0 || idx >= m_techniques.size())
    {
        return nullptr;
    }

    return m_techniques[idx];
}
