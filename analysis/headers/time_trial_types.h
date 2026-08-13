#ifndef TIME_TRIAL_TYPES_H
#define TIME_TRIAL_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRTimeTrial. The Windows size ledger fixes the owner at 0x330 bytes;
 * Android cRTimeTrial::Init() independently proves 51 inline 0x10-byte
 * records and writes the leading course-name pointer in each record.
 */

typedef unsigned char uint8_t;

enum {
    TIME_TRIAL_COURSE_RECORD_COUNT = 51,
};

typedef struct TimeTrialCourseRecord {
    char* course_name;
    uint8_t unknown_04[0x10 - 0x04];
} TimeTrialCourseRecord;

typedef char TimeTrialCourseRecord_must_be_0x10[
    (sizeof(TimeTrialCourseRecord) == 0x10) ? 1 : -1];

typedef struct cRTimeTrial {
    TimeTrialCourseRecord course_records[TIME_TRIAL_COURSE_RECORD_COUNT];
} cRTimeTrial;

typedef char cRTimeTrial_must_be_0x330[
    (sizeof(cRTimeTrial) == 0x330) ? 1 : -1];

#endif
