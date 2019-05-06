#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <core/base_math.h>
#include <resource/resource_mgr.h>
#include <core/string_ex.h>
#include <core/timer.h>


class App
{
public:
    bool Init(const String& title, int width = 640, int height = 480);
    void Run();
    void Destory();

protected:
    virtual void OnInit() {}
    virtual void OnUpdate() {}
    virtual void OnDestroy() {}

protected:
    GLFWwindow * m_window;
    int m_width;
    int m_height;
};