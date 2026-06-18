// Parcel row-event display controller view, partial.
#ifndef ROW_EVENT_DISPLAY_H
#define ROW_EVENT_DISPLAY_H

#include "frontend_widget.h"

class RowEventDisplayController {
public:
    void flush_row_event_display();    // @ 0x404830
    void register_parcel_delivery();   // @ 0x405040

    FrontendWidget* widget_a;   // +0x00
    FrontendWidget* delivered_count_widget; // +0x04
    FrontendWidget* bonus_widget;           // +0x08
    FrontendWidget* widget_d;   // +0x0c
    FrontendWidget* continue_widget;        // +0x10
    int state;                  // +0x14
    unsigned char gate_18;      // +0x18
    char unknown_19[0x1c - 0x19];
    int parcel_target_count;    // +0x1c
    int bonus_enabled;          // +0x20
    int staged_parcel_count;    // +0x24
    int delivered_parcel_count; // +0x28
    float progress;             // +0x2c
    float progress_step;        // +0x30
    float widget_world_x;       // +0x34
    float widget_world_y;       // +0x38
    float widget_world_z;       // +0x3c
    float bonus_blink_progress; // +0x40
    float bonus_blink_step;     // +0x44
    int bonus_score;            // +0x48
    int display_token;          // +0x4c
};

#endif
