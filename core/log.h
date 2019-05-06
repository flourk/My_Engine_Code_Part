#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <string>

class SceneNode;

class Log {
public:
    Log(std::ostream& out = std::cout) : m_out(out)
    {        
    }

    virtual ~Log()
    {
    }

    friend Log& operator<<(Log& log, const glm::mat4& value);
    friend Log& operator<<(Log& log, const glm::vec4& value);
    friend Log& operator<<(Log& log, const glm::quat& value);
    friend Log& operator<<(Log& log, const std::string value);

    void PrintTree(SceneNode* node);

private:
    std::ostream& m_out;
};

extern Log logConsole;