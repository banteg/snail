// Delayed frontend-widget flag lane stored on the root gameplay object.
#ifndef BORDER_DELAY_LANE_H
#define BORDER_DELAY_LANE_H

#include "frontend_widget.h"

class FrontendFade {
public:
    int begin_frontend_fade_out(int hold_state);
    void begin_frontend_fade_in();

    int state; // +0x00
    int alpha_bits; // +0x04
    int field_08; // +0x08
    int field_0c; // +0x0c
    int hold_state; // +0x10
};

class BorderDelayLane {
public:
    char queue_frontend_widget_flag_after_delay(
        FrontendWidget* widget, int queued_flags); // @ 0x403f60
    void update_border_manager(); // @ 0x403fc0

    char unknown_00000[0x4359c];
    int delayed_widget_flags; // +0x4359c
    char delayed_widget_active; // +0x435a0
    char unknown_435a1[0x435a4 - 0x435a1];
    float delayed_widget_progress; // +0x435a4
    float delayed_widget_progress_step; // +0x435a8
    FrontendWidget* delayed_widget; // +0x435ac
};

#endif
