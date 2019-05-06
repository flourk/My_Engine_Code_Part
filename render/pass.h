#pragma once
#include "device/gpu_types.h"
#include "core/string_ex.h"
#include "device/gpu_program.h"

class Parameter;

struct RasterState
{
    bool cullEnable;
    CullFace cullFace;
    CullFrontFace cullFrontFace;
};


struct ShaderCode
{
    String name;
    String code;
};


class Pass
{
public:
    void Compile();
    RasterState& GetRasterState() { return m_rasterState; }
    const RasterState& GetRasterState() const { return m_rasterState; }
    const GpuProgram& GetGpuProgram() const { return m_program; }

    const String& GetName() const { return m_name; }
    void SetName(const String& name) { m_name = name; }

    ShaderCode& GetVertexShaderCode() { return m_vertex; }

    ShaderCode& GetFragmentShaderCode() { return m_fragment; }

private:
    RasterState m_rasterState;

    ShaderCode m_vertex;
    ShaderCode m_fragment;
    GpuProgram m_program;

    String m_name;
};