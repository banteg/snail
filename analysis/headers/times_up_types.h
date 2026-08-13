#ifndef TIMES_UP_TYPES_H
#define TIMES_UP_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRTimesUp tail at cRSubGame +0x1272828. Android preserves all three method
 * bodies and the exact 0x10-byte layout; iOS independently preserves the
 * authored class-qualified Init and AI ownership and reports sizeof 0x10.
 */

typedef struct FrontendWidget FrontendWidget;

typedef enum TimesUpState {
    TIMES_UP_STATE_INACTIVE = 0,
    TIMES_UP_STATE_DISPLAYING = 1,
    TIMES_UP_STATE_EXPIRED = 2,
} TimesUpState;

typedef struct cRTimesUp {
    TimesUpState state;
    FrontendWidget* border;
    float progress;
    float progress_step;
} cRTimesUp;

typedef char cRTimesUp_must_be_0x10[
    (sizeof(cRTimesUp) == 0x10) ? 1 : -1];

#endif
