#ifndef WARNING_TYPES_H
#define WARNING_TYPES_H

/*
 * Narrow cross-decompiler ownership slice for the shipped Windows
 * cRWarning controller. Mobile builds retain the same lifecycle and roles,
 * but carry additional presentation fields before the border pointer.
 */

typedef enum WarningState {
    WARNING_STATE_INACTIVE = 0,
    WARNING_STATE_OPAQUE = 1,
    WARNING_STATE_FADING = 2,
} WarningState;

struct FrontendWidget;

typedef struct cRWarning {
    WarningState state;
    float phase;
    float phase_step;
    struct FrontendWidget* border;
} cRWarning;

typedef char cRWarning_must_be_0x10[(sizeof(cRWarning) == 0x10) ? 1 : -1];

#endif
