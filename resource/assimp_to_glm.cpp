#include "assimp_to_glm.h"
#include <memory>

namespace AssimpToGLM {
    glm::mat4 aiToGLM(const aiMatrix4x4& inV)
    {
        glm::mat4 outV;
        std::memcpy(&outV, &inV, sizeof(inV));
        return glm::transpose(outV);
    }

    glm::vec3 aiToGLM(const aiVector3D& inV)
    {
        glm::vec3 outV;
        std::memcpy(&outV, &inV, sizeof(inV));
        return outV;
    }

    glm::quat aiToGLM(const aiQuaternion& inV)
    {
        return glm::quat(inV.w, inV.x, inV.y, inV.z);
    }
};