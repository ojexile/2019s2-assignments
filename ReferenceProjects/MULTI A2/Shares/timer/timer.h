#ifndef _TIMER_H
#define _TIMER_H

#include <windows.h>

class Timer
{
    private:
        bool     s_bUsingQPF = false;
        LONGLONG s_llQPFTicksPerSec = 0;
        LONGLONG s_llLastElapsedTime = 0;

    public:
        Timer();
        ~Timer();

    public:
        float GetTimer_sec( void );
        float GetTimer_msec( void );
};

#endif // _TIMER_H