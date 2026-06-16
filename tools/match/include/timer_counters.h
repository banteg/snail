// Subgame timer counter view, partial.
#ifndef TIMER_COUNTERS_H
#define TIMER_COUNTERS_H

class TimerCounters {
public:
    int zero_timer_counters(); // @ 0x441b70
    int advance_timer_counters(float delta_ticks); // @ 0x441b90

    float total_seconds;        // +0x00
    int minutes;                // +0x04
    int frames_into_second;     // +0x08
    int display_hundredths;     // +0x0c
    int display_thousandths;    // +0x10
    float second_fraction;      // +0x14
};

typedef char TimerCounters_must_be_0x18[
    (sizeof(TimerCounters) == 0x18) ? 1 : -1];

#endif
