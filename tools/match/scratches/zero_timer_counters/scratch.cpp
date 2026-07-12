// cRTime::Zero / zero_timer_counters @ 0x441b70 (thiscall, ret)

#include "game_time.h"

void Time::Zero()
{
    total_seconds = 0.0f;
    minutes = 0;
    seconds = 0;
    display_hundredths = 0;
    display_thousandths = 0;
    second_fraction = 0.0f;
}
