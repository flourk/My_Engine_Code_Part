#pragma once

#include <vector>

class Pass;

class Technique
{
public:
    void AddPass(Pass* pass) { m_passes.push_back(pass); }
    Pass* GetPass(int idx);

    int GetPassCount() { return m_passes.size(); }
    
    void Compile();

private:
    std::vector<Pass*> m_passes;
};