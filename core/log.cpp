#include "log.h"
#include <scene/scene_node.h>
#include <functional>

Log logConsole;

Log& operator<<(Log& log, const glm::mat4& value)
{
    static const char* space = "    ";
    log.m_out << std::endl << "mat4:" << std::endl;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            log.m_out << value[i][j];
            if(j < 3)
            {
                log.m_out << space;
            }
        }

        log.m_out << std::endl;
    }

    log.m_out << std::endl;

    return log;
}

Log& operator<<(Log& log, const glm::vec4& value)
{
    log.m_out << "(" << value[0] << ", " << value[1] << ", " << 
        value[2] << ", " << value[3] << ")" << std::endl;
    return log;
}

Log& operator<<(Log& log, const glm::quat& value)
{
    log.m_out << "(" << value.x << ", " << value.y << ", " << 
    value.z << ", " << value.w << ")" << std::endl;
    return log;
}



Log& operator<<(Log& log, const std::string value)
{
    log.m_out << value << std::endl;
    return log;
}


void Log::PrintTree(SceneNode* node)
{
    std::function<void(SceneNode*, int)> printTreeDepth = [&](SceneNode* node, int depth)
    {
        for(int i = 0; i < depth; i++)
        {
            m_out << "    ";
        }
        m_out << node->mName << std::endl;

        auto children = node->GetChildren();
        for(auto i = 0; i < children.size(); i++)
        {
            printTreeDepth(children[i], depth + 1);
        }
    };

    m_out << "Scene Tree : " << std::endl;
    printTreeDepth(node, 0);
}
