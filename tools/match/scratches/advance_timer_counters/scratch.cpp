// advance_timer_counters @ 0x441b90 (thiscall, ret 0x4)

#include "timer_counters.h"

int TimerCounters::advance_timer_counters(float delta_ticks)
{
    float delta_seconds = delta_ticks * 0.0166666675f;
    total_seconds += delta_seconds;

    float fraction = second_fraction + delta_seconds;
    second_fraction = fraction;
    if (fraction >= 1.0f) {
        frames_into_second += 1;
        int compare_frames = frames_into_second;
        second_fraction = fraction - 1.0f;
        if (compare_frames >= 60) {
            frames_into_second = compare_frames - 60;
            minutes += 1;
        }
    }

    display_hundredths = (int)(second_fraction * 100.0f);
    display_thousandths = (int)(second_fraction * 1000.0f);
    return display_thousandths;
}
