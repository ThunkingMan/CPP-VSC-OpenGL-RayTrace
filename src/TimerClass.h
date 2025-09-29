//Timer Class
#pragma once
#define WIN32_LEAN_AND_MEAN


class TimerClass {
public:
    TimerClass();
    TimerClass(const TimerClass&);
    ~TimerClass();
    bool Init();
    void GetDeltaTime();

    unsigned _int16 m_FrameDeltaMS;
    unsigned _int32 m_RndSeed; //smi random seed ueed for random number generator

private:
    unsigned _int16 m_TicksPerMS; //Timer freqency per mili second
    unsigned _int64 m_CurrentCount; //Current timer count
    unsigned _int64 m_PreviousCount; //Prevous timer count
};
