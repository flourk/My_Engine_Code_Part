#pragma once

#include <assimp/scene.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace AssimpToGLM {
    glm::mat4 aiToGLM(const aiMatrix4x4& inV);
    glm::vec3 aiToGLM(const aiVector3D& inV);
    glm::quat aiToGLM(const aiQuaternion& inV);
};