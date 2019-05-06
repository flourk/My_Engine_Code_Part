#pragma once

class Timer {
public:
    static float GetDeltaTime() { return m_deltaTime; }
    static float GetTimeSinceStart() { return m_timeSinceStart; }
    static float GetStartTime() { return m_startTime; }

    static void Initialize();
    static void Update();


private:
    static float m_startTime;
    static float m_timeSinceStart;
    static float m_deltaTime;
    static float m_preTime;
};