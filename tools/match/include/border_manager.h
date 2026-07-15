// Shared border manager view, cross-checked by the border allocation,
// batch visibility, activation, teardown, tip, and row-event paths.
#ifndef BORDER_MANAGER_H
#define BORDER_MANAGER_H

#include "bod_types.h"
#include "border_batch_state.h"
#include "frontend_widget.h"

class BorderRecord : public BodBase {
public:
    BorderRecord* initialize_border_record(); // @ 0x408410

    char unknown_038[0x6c - 0x038];
    tColour color_06c; // +0x06c, constructor-proven color/style block
    char unknown_07c[0x19c - 0x07c];
    int created_time; // +0x19c
    int flags; // +0x1a0, FrontendWidgetFlag word in backing storage
    char unknown_1a4[0x1ac - 0x1a4];
    tColour color_1ac; // +0x1ac
    tColour color_1bc; // +0x1bc
    tColour color_1cc; // +0x1cc
    tColour color_1dc; // +0x1dc
    tColour color_1ec; // +0x1ec
    tColour color_1fc; // +0x1fc
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

enum {
    BORDER_RECORD_COUNT = 150,
};

class BorderManager : public BodBase {
public:
    // The backing storage is BorderRecord-sized, but frontend callers use the
    // returned record through the FrontendWidget view.
    FrontendWidget* allocate_border(); // @ 0x4032a0
    void activate_all_borders(); // @ 0x403300
    void kill_all_borders(); // @ 0x4033c0, cRBorderManager::KillBorders
    void hide_all_borders(); // @ 0x4033f0, iOS cRBorderManager::HideBorders()
    void unhide_all_borders(); // @ 0x403400, iOS cRBorderManager::UnHideBorders()
    int kill_border(FrontendWidget* border);
    char queue_frontend_widget_flag_after_delay(
        FrontendWidget* widget, int queued_flags); // @ 0x403f60
    void update_border_manager(); // @ 0x403fc0
    int set_border_justify_centre(int justify_centre_bits); // @ 0x404730

    BorderStack border_stack; // +0x38, exact cRBorderStack owner/link history
    BorderRecord borders[BORDER_RECORD_COUNT]; // +0x684
    // One transition lane follows the fixed border pool. While active it
    // gates front-end input and drives the target widget's wobble/glow until
    // the queued flags are applied.
    int delayed_widget_flags; // +0x4359c
    unsigned char delayed_widget_active; // +0x435a0
    char unknown_435a1[0x435a4 - 0x435a1];
    float delayed_widget_progress; // +0x435a4
    float delayed_widget_progress_step; // +0x435a8
    FrontendWidget* delayed_widget; // +0x435ac, borrowed border handle
    union {
        int justify_centre_bits; // +0x435b0, mutator preserves raw float bits
        float justify_centre; // +0x435b0, added to authored widget anchors
    };
};

typedef char BorderManager_must_be_0x435b4[
    (sizeof(BorderManager) == 0x435b4) ? 1 : -1];

#endif
