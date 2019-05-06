#pragma once

#include "technique.h"
#include "pass.h"

Pass* Technique::GetPass(int idx)
{
    if(idx < 0 || idx >= m_passes.size())
        return nullptr;

    return m_passes[idx];
}

void Technique::Compile()
{
    for(int i = 0; i < m_passes.size(); i++)
    {
        m_passes[i]->Compile();
    }
}
 

