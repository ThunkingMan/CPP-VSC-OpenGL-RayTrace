
#include "TimerClass.h"
#include "windows.h"
#include <cstdio>

TimerClass::TimerClass() {}
TimerClass::TimerClass(const TimerClass&) {}
TimerClass::~TimerClass() {}

bool TimerClass::Init() {
    LARGE_INTEGER CounterFreq;
    QueryPerformanceFrequency(&CounterFreq);
    if (CounterFreq.QuadPart == 0) {
        std::printf("Error: Cant init timer class\n.");
        return false;
    }
    m_TicksPerMS = CounterFreq.QuadPart / 1000; //Counter ticks per milli second.
    
    LARGE_INTEGER TmpCount;
    QueryPerformanceCounter(&TmpCount);
    m_RndSeed = TmpCount.LowPart; //General semi random number seed.
    m_PreviousCount = TmpCount.QuadPart;
    return true;
}

void TimerClass::GetDeltaTime() {
    LARGE_INTEGER TmpCount;
    QueryPerformanceCounter(&TmpCount);
    m_CurrentCount = TmpCount.QuadPart;
    m_FrameDeltaMS = (m_CurrentCount - m_PreviousCount) / m_TicksPerMS;
    m_PreviousCount = m_CurrentCount;
}