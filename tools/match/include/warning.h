// Authored cRWarning HUD controller. Windows uses this exact 0x10-byte layout;
// mobile variants add two presentation lanes before the border pointer.
#ifndef WARNING_H
#define WARNING_H

#include "frontend_widget.h"

class Warning {
public:
    void initialize_warning(); // @ 0x446e80, cRWarning::Init
    void uninit_warning(); // @ 0x446f10, cRWarning::UnInit
    void start_warning(); // @ 0x446f30, cRWarning::Start
    void stop_warning(); // @ 0x446f50, cRWarning::Stop
    void stop_warning_sample(); // @ 0x446f60, cRWarning::StopSample
    void update_warning(); // @ 0x446f80, cRWarning::AI

    int state; // +0x00: 0 idle, 1 fill, 2 fade
    float phase; // +0x04
    float phase_step; // +0x08
    FrontendWidget* border; // +0x0c
};

typedef char Warning_must_be_0x10[(sizeof(Warning) == 0x10) ? 1 : -1];

#endif
