#pragma once
#include <GL/glew.h>

class GpuObj
{
public:
    GpuObj() = default;

    GLuint GetHandler() const { return m_handler; }
    void SetHandler(GLuint value) { m_handler = value; }

private:
    GLuint m_handler;
};