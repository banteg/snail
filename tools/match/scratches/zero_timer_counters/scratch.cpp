// zero_timer_counters @ 0x441b70 (thiscall, ret)

#include "timer_counters.h"

int TimerCounters::zero_timer_counters()
{
    total_seconds = 0.0f;
    minutes = 0;
    frames_into_second = 0;
    display_hundredths = 0;
    display_thousandths = 0;
    second_fraction = 0.0f;
    return 0;
}
