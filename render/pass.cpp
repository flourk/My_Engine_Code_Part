#include "pass.h"
#include <core/log.h>

#include <memory.h>

void PrintUniforms(GLuint programId)
{
    static char buff[512];

    GLint uniformCount = 0;
    GLint maxUniformLen = 0;
    glGetProgramiv(programId, GL_ACTIVE_UNIFORMS, &uniformCount);
    glGetProgramiv(programId, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);

    memset(buff, 0, sizeof(buff));

    GLint size;
    GLenum type;

    for(int i = 0; i < uniformCount; i++)
    {

        glGetActiveUniform(programId, i, maxUniformLen, nullptr, &size, &type, buff);
        logConsole << buff;
    }
}

void Pass::Compile()
{
    logConsole << "(pass) Compiling Pass: " + m_name;

    logConsole << "(pass) Compiling Vertex : " + m_vertex.name;
    GLuint vsShader = glCreateShader(GL_VERTEX_SHADER);
    const char* code = m_vertex.code.c_str();
    glShaderSource(vsShader, 1, &code, nullptr);
    glCompileShader(vsShader);

    char buff[1024] = {0};

    int success = 0;
    glGetShaderiv(vsShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vsShader, 1024, nullptr, buff);
        logConsole << "vertex shader error : \n" << buff;
        logConsole << code << "\n\n";
    }

 //           logConsole << "(pass) " << code << "\n\n";


    logConsole << "(pass) Compiling Fragment : " + m_fragment.name;
    GLuint fsShader = glCreateShader(GL_FRAGMENT_SHADER);
    code = m_fragment.code.c_str();
    glShaderSource(fsShader, 1, &code, nullptr);
    glCompileShader(fsShader);

    glGetShaderiv(vsShader, GL_COMPILE_STATUS, &success);
    
    if(!success)
    {
        glGetShaderInfoLog(vsShader, 1024, nullptr, buff);
        logConsole << "(pass) fragment shader error : " << buff;
        logConsole << code << "\n\n";
    }

//            logConsole << "(pass) " << code << "\n\n";


    int programId = glCreateProgram();
    glAttachShader(programId, vsShader);
    glAttachShader(programId, fsShader);
    glLinkProgram(programId);

    glGetProgramiv(programId, GL_LINK_STATUS, &success);

    if(!success)
    {
        glGetProgramInfoLog(programId, 1024, nullptr, buff);
        logConsole << "link error : " << buff;
    }

    // PrintUniforms(programId);

    // glGetProgramInfoLog (m_program, 1024, nullptr, buff);
    // cout << buff << endl;

    m_program.SetHandler(programId);
}