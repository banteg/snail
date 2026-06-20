// Time-trial display formatting service. The native method writes a shared
// text buffer and does not expose formatter-owned fields.
#ifndef TIME_TRIAL_STRING_FORMATTER_H
#define TIME_TRIAL_STRING_FORMATTER_H

#include "timer_counters.h"

class TimeTrialStringFormatter {
public:
    char* format_time_trial_string(TimerCounters* timer); // @ 0x448960
};

#endif
