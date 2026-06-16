// Tip/tutorial message runtime views, partial.
#ifndef TIP_MANAGER_H
#define TIP_MANAGER_H

class FrontendWidget;

struct TipMessageDefinition {
    unsigned int flags;        // +0x00
    float layout_y;            // +0x04
    float text_scale;          // +0x08
    float dismiss_seconds;     // +0x0c
    char* text;                // +0x10
};

class TipSlot {
public:
    void initialize_tip(TipMessageDefinition* definition, int show_disable_button); // @ 0x448a40
    void kill_tip_widgets(); // @ 0x4489e0
    void update_tip(); // @ 0x448c40

    int active;                         // +0x00
    int previous_outer_owner;           // +0x04
    TipMessageDefinition* definition;   // +0x08
    FrontendWidget* widget_main;        // +0x0c
    FrontendWidget* widget_ok;          // +0x10
    FrontendWidget* widget_disable;     // +0x14
    float dismiss_progress;             // +0x18
    float dismiss_step;                 // +0x1c
};

class TipManager {
public:
    void initialize_tip_manager(); // @ 0x448cf0
    void uninit_tips(); // @ 0x448d10
    TipSlot* enqueue_tip_message(TipMessageDefinition* definition, int show_disable_button); // @ 0x448d30
    void update_tip_manager(); // @ 0x448d80

    char unknown_00[0x38];
    TipSlot slots[3]; // +0x38
};

typedef char TipMessageDefinition_must_be_0x14[
    (sizeof(TipMessageDefinition) == 0x14) ? 1 : -1];
typedef char TipSlot_must_be_0x20[(sizeof(TipSlot) == 0x20) ? 1 : -1];
typedef char TipManager_must_be_0x98[
    (sizeof(TipManager) == 0x98) ? 1 : -1];

#endif
