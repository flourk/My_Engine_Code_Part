#include "timer.h"
#include <GLFW/glfw3.h>

float Timer::m_startTime = 0.0f;
float Timer::m_timeSinceStart = 0.0f;
float Timer::m_deltaTime = 0.0f;
float Timer::m_preTime = 0.0f;

void Timer::Initialize()
{
#ifndef Editor
    m_startTime = glfwGetTime();
    m_timeSinceStart = 0;
    m_deltaTime = 0;
    m_preTime = m_startTime;
#endif
}
void Timer::Update()
{
#ifndef Editor
    float curTime = glfwGetTime();
    m_timeSinceStart = curTime - m_startTime;
    m_deltaTime = curTime - m_preTime;
    m_preTime = curTime;
#endif
}