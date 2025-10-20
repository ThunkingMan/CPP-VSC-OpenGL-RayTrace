//Timer Class
#pragma once
#define WIN32_LEAN_AND_MEAN
#include <stdint.h>


class TimerClass {
public:
    TimerClass();
    TimerClass(const TimerClass&);
    ~TimerClass();
    bool Init();
    void GetDeltaTime();

    uint16_t m_FrameDeltaMS;
    uint32_t m_RndSeed; //smi random seed ueed for random number generator

private:
    uint16_t m_TicksPerMS; //Timer freqency per mili second
    uint64_t m_CurrentCount; //Current timer count
    uint64_t m_PreviousCount; //Prevous timer count
};
