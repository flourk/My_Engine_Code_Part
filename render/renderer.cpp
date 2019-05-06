#include "renderer.h"
#include <GL/glew.h>
#include <scene/scene_node.h>
#include <scene/camera.h>
#include <scene/light_manager.h>

#include "device/gl_helper.h"
#include "parameter.h"

Renderer gRenderer;

static void SetValueTable(const GpuProgram& program, const std::map<String, Variant>& table)
{
    GLuint handler = program.GetHandler();

    for(auto it = table.begin(); it != table.end(); it++)
    {
        const char* name = it->first.c_str();
        GLint loc = glGetUniformLocation(handler, name);
        if(loc < 0)
            continue;

        const Variant& variant = it->second;
        switch (variant.GetType())
        {
        case Variant::Type::VT_Float:
            {
                glUniform1f(loc, variant.GetFloat());
            }
            break;
        case Variant::Type::VT_Int:
            {
                glUniform1d(loc, variant.GetInt());
            }
            break;
        case Variant::Type::VT_Vec4f:
            {
                const Vec4f& value = variant.GetVec4f();
                glUniform4fv(loc, 1, glm::value_ptr(value));
            }
            break;
        case Variant::Type::VT_Mat4:
            {
                const Mat4& value = variant.GetMat4();
                glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(value));
            }
            break;
        default:
            break;
        }
    }
} 

static void SetTextureTable(const GpuProgram& program, const std::map<TextureSlot, Texture*>& table)
{
    GLuint handler = program.GetHandler();

    for(auto it = table.begin(); it != table.end(); it++)
    {
        const TextureSlot& slot = it->first;
        const char* name = slot.name.c_str();
        GLint loc = glGetUniformLocation(handler, name);

        if(loc < 0)
            continue;

        glActiveTexture(GL_TEXTURE0 + slot.num);
        GLuint handler = it->second->GetHandler();

        glBindTexture(GL_TEXTURE_2D, it->second->GetHandler());

        glUniform1i(loc, slot.num);
    }
}

void Renderer::RenderScene(SceneNode* rootNode, Camera* camera)
{
    rootNode->Render(camera);
}


void Renderer::SetPass(const Pass& pass, const Parameter& param)
{
    const RasterState& raster = pass.GetRasterState();
    if(raster.cullEnable)
    {
        glEnable(GL_CULL_FACE);
        glFrontFace(GLHelper::ToGLEnum(raster.cullFrontFace));
        glCullFace(GLHelper::ToGLEnum(raster.cullFace));
    }
    else
    {
        glDisable(GL_CULL_FACE);
    }

    const GpuProgram& program = pass.GetGpuProgram();
    glUseProgram(program.GetHandler());

    SetValueTable(program, param.GetValueTable());
    SetTextureTable(program, param.GetTextureTable());
}
