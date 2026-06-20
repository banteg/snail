// Delayed frontend-widget flag lane stored on the root gameplay object.
#ifndef BORDER_DELAY_LANE_H
#define BORDER_DELAY_LANE_H

#include "frontend_fade.h"
#include "frontend_widget.h"

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
