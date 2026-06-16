// Warning HUD actor view, partial. The +0x0c target is the warning
// FrontendWidget allocated by initialize_warning; update_warning drives its
// overlay alpha lane at widget+0x208.
#ifndef WARNING_ACTOR_H
#define WARNING_ACTOR_H

#include "frontend_widget.h"

class WarningActor {
public:
    void initialize_warning(); // @ 0x446e80
    void uninit_warning(); // @ 0x446f10
    void start_warning(); // @ 0x446f30
    void stop_warning(); // @ 0x446f50
    void stop_warning_sample(); // @ 0x446f60, callee ignores ecx
    void update_warning(); // @ 0x446f80

    int state; // +0x00: 0 idle, 1 fill, 2 fade
    float phase; // +0x04
    float phase_step; // +0x08
    FrontendWidget* border; // +0x0c
};

typedef char WarningActor_must_be_0x10[
    (sizeof(WarningActor) == 0x10) ? 1 : -1];

#endif
