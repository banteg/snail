// Shared border manager view, cross-checked by the border allocation,
// batch visibility, activation, teardown, tip, and row-event paths.
#ifndef BORDER_MANAGER_H
#define BORDER_MANAGER_H

#include "border_batch_state.h"
#include "frontend_widget.h"

class BorderRecord {
public:
    char unknown_000[0x19c];
    int created_time; // +0x19c
    int flags; // +0x1a0
    char unknown_1a4[0x20c - 0x1a4];
    float hover_blend_target; // +0x20c
    float hover_blend_current; // +0x210
    float idle_padding; // +0x214
    float hot_padding; // +0x218
    float target_padding; // +0x21c
    float active_padding; // +0x220
    char unknown_224[0x724 - 0x224];
};

typedef char BorderRecord_must_be_0x724[
    (sizeof(BorderRecord) == 0x724) ? 1 : -1];

class BorderManager {
public:
    BorderRecord* allocate_border(); // @ 0x4032a0
    void activate_all_borders(); // @ 0x403300
    int kill_all_borders(); // @ 0x4033c0
    int hide_all_borders(); // @ 0x4033f0
    int unhide_all_borders(); // @ 0x403400
    void kill_border(FrontendWidget* border);

    char unknown_000[0x38];
    BorderBatchState batch_state; // +0x38
    char unknown_039[0x684 - 0x039];
    BorderRecord borders[150]; // +0x684
};

#endif
