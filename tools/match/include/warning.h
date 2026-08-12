// Authored cRWarning HUD controller. Windows uses this exact 0x10-byte layout;
// mobile variants add two presentation lanes before the border pointer.
#ifndef WARNING_H
#define WARNING_H

#include "frontend_widget.h"

enum WarningState {
    WARNING_STATE_INACTIVE = 0,
    WARNING_STATE_OPAQUE = 1,
    WARNING_STATE_FADING = 2,
};

class cRWarning {
public:
    void Init(); // @ 0x446e80
    void UnInit(); // @ 0x446f10
    void Start(); // @ 0x446f30
    void Stop(); // @ 0x446f50
    void StopSample(); // @ 0x446f60, receiver unused by Windows body
    void AI(); // @ 0x446f80

    WarningState state; // +0x00
    float phase; // +0x04
    float phase_step; // +0x08
    cRBorder* border; // +0x0c
};

typedef cRWarning Warning;

typedef char cRWarning_must_be_0x10[(sizeof(cRWarning) == 0x10) ? 1 : -1];
typedef char Warning_must_be_0x10[(sizeof(Warning) == 0x10) ? 1 : -1];

#endif
