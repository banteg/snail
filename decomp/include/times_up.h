// Authored cRTimesUp owner embedded at the tail of cRSubGame.
#ifndef TIMES_UP_H
#define TIMES_UP_H

#include "frontend_widget.h"

enum TimesUpState {
    TIMES_UP_STATE_INACTIVE = 0,
    TIMES_UP_STATE_DISPLAYING = 1,
    TIMES_UP_STATE_EXPIRED = 2,
};

class cRTimesUp {
public:
    void AI();     // @ 0x445e20
    void UnInit(); // @ 0x445e70
    void Init();   // @ 0x445e90

    TimesUpState state; // +0x00
    cRBorder* border; // +0x04, borrowed cRBorderManager handle
    float progress; // +0x08
    float progress_step; // +0x0c
};

typedef cRTimesUp TimesUp;
typedef char TimesUp_must_be_0x10[
    (sizeof(cRTimesUp) == 0x10) ? 1 : -1];

#endif
