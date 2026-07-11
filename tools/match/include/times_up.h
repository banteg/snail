// Authored cRTimesUp owner embedded at the tail of SubgameRuntime.
#ifndef TIMES_UP_H
#define TIMES_UP_H

#include "frontend_widget.h"

class TimesUp {
public:
    void update_times_up(); // @ 0x445e20, cRTimesUp::AI
    void uninit_times_up(); // @ 0x445e70, cRTimesUp::UnInit
    void show_times_up_message(); // @ 0x445e90, cRTimesUp::Init

    int state; // +0x00
    FrontendWidget* border; // +0x04, borrowed BorderManager handle
    float progress; // +0x08
    float progress_step; // +0x0c
};

typedef char TimesUp_must_be_0x10[
    (sizeof(TimesUp) == 0x10) ? 1 : -1];

#endif
