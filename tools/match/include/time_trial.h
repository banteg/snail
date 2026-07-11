// Authored cRTimeTrial owner embedded in SubgameRuntime at +0xff25e0. The
// following proven cRPathManager begins at +0xff2910, giving this object the
// exact 0x330-byte extent printed by the Windows runtime size ledger.
#ifndef TIME_TRIAL_H
#define TIME_TRIAL_H

#include "timer_counters.h"

class TimeTrial {
public:
    char* format_time_trial_string(
        TimerCounters* timer); // @ 0x448960, cRTimeTrial::TimeString(cRTime&)

    // TimeString does not read receiver fields. The owner extent and placement
    // are independently fixed by the adjacent PathManager and size ledger.
    char unknown_000[0x330];
};

typedef char TimeTrial_must_be_0x330[
    (sizeof(TimeTrial) == 0x330) ? 1 : -1];

#endif
