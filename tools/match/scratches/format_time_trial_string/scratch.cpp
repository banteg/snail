// format_time_trial_string @ 0x448960 (stdcall, ret 0x4)

#include "timer_counters.h"

int sprintf(char* buffer, char* format, ...);

extern char g_time_trial_string[]; // 0x751478

char* __stdcall format_time_trial_string(TimerCounters* timer)
{
    if (timer->total_seconds == 0.0f) {
        sprintf(g_time_trial_string, "-:--:--");
    } else {
        sprintf(
            g_time_trial_string,
            "%1i:%02i:%03i",
            timer->minutes,
            timer->frames_into_second,
            timer->display_thousandths);
        sprintf(
            g_time_trial_string,
            "%1i:%02i:%02i",
            timer->minutes,
            timer->frames_into_second,
            timer->display_hundredths);
    }

    return g_time_trial_string;
}
