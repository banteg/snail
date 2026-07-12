// Authored cRTime value shared by player, level, and high-score state.
#ifndef GAME_TIME_H
#define GAME_TIME_H

class Time {
public:
    void Zero(); // @ 0x441b70, cRTime::Zero()
    void Add(float delta_ticks); // @ 0x441b90, cRTime::Add(float)

    float total_seconds;        // +0x00
    int minutes;                // +0x04
    int seconds;                // +0x08, seconds within the current minute
    int display_hundredths;     // +0x0c
    int display_thousandths;    // +0x10
    float second_fraction;      // +0x14
};

typedef char Time_must_be_0x18[
    (sizeof(Time) == 0x18) ? 1 : -1];

#endif
