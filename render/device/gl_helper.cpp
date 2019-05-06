#include "gl_helper.h"
#include <GL/glew.h>"

#include <map>

using namespace std;

namespace GLHelper
{
    int ToGLEnum(CullFace cullFace)
    {
        static map<CullFace, GLenum> table =
        {
            { CULL_FRONT, GL_FRONT },
            { CULL_BACK, GL_BACK },
            { CULL_FRONT_AND_BACK, GL_FRONT_AND_BACK}
        };

        return table[cullFace];
    }

    int ToGLEnum(CullFrontFace frontFace)
    {
        static map<CullFrontFace, GLenum> table =
        {
            { CULL_CW, GL_CW },
            { CULL_CCW, GL_CCW }
        };

        return table[frontFace];
    }

} // namespace GPUHelper
