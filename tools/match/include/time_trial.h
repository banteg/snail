// Authored cRTimeTrial owner embedded in cRSubGame at +0xff25e0. The
// following proven cRPathManager begins at +0xff2910, giving this object the
// exact 0x330-byte extent printed by the Windows runtime size ledger.
#ifndef TIME_TRIAL_H
#define TIME_TRIAL_H

#include "game_time.h"

enum {
    TIME_TRIAL_COURSE_RECORD_COUNT = 51,
};

// Android cRTimeTrial::Init copies gTimeTrialCourseNames into the first word
// of 51 consecutive 0x10-byte records. The remaining record lanes are not yet
// referenced by a named routine and stay deliberately opaque.
struct TimeTrialCourseRecord {
    char* course_name;
    char unknown_04[0x10 - 0x04];
};

typedef char TimeTrialCourseRecord_must_be_0x10[
    (sizeof(TimeTrialCourseRecord) == 0x10) ? 1 : -1];

class TimeTrial {
public:
    char* format_time_trial_string(
        Time* timer); // @ 0x448960, cRTimeTrial::TimeString(cRTime&)

    TimeTrialCourseRecord course_records[
        TIME_TRIAL_COURSE_RECORD_COUNT];
};

typedef char TimeTrial_must_be_0x330[
    (sizeof(TimeTrial) == 0x330) ? 1 : -1];

#endif
