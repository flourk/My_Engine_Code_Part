#include "app.h"

bool App::Init(const String& title, int width, int height)
{
    /* Initialize the library */
    if (!glfwInit())
        return false;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    m_width = width > 0 ? width : 640;
    m_height = height > 0? height : 480;

    m_window = glfwCreateWindow(m_width, m_height, title.c_str(), NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        return false;
    }


    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    glewExperimental = GL_TRUE;
    glewInit();

    ResourceMgr::RegisterLoaders();
    ResourceMgr::PreCacheShader();

    OnInit();

    return true;
}

void App::Run()
{
    glViewport(0, 0, m_width, m_height);

    while (!glfwWindowShouldClose(m_window)) 
    {
        /* Poll for and process events */
        glfwPollEvents();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Timer::Update();

        OnUpdate();

        /* Swap front and back buffers */
        glfwSwapBuffers(m_window);
    }
}

void App::Destory()
{
    OnDestroy();
    glfwDestroyWindow(m_window);
    m_window = nullptr;
    glfwTerminate();
}