#ifndef TIME_TYPES_H
#define TIME_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows cRTime.
 * The exact Zero/Add pair covers all six fields; Android independently
 * preserves the complete owner and both mobile ports preserve the authored
 * class-qualified method names.
 */

typedef int int32_t;

/* The formatter borrows this independently recovered owner. */
typedef struct cRTimeTrial cRTimeTrial;

typedef struct cRTime {
    float total_seconds;
    int32_t minutes;
    int32_t seconds;
    int32_t display_hundredths;
    int32_t display_thousandths;
    float second_fraction;
} cRTime;

typedef char cRTime_must_be_0x18[
    (sizeof(cRTime) == 0x18) ? 1 : -1];

#endif
