// Tip/tutorial message runtime views, partial.
#ifndef TIP_MANAGER_H
#define TIP_MANAGER_H

#include "bod_types.h"

class FrontendWidget;

struct TipData {
    unsigned int flags;        // +0x00
    float layout_y;            // +0x04
    float text_scale;          // +0x08
    float dismiss_seconds;     // +0x0c
    char* text;                // +0x10
};
typedef TipData TipMessageDefinition;

class Tip {
public:
    void initialize_tip(TipData* definition, int hide_disable_button); // @ 0x448a40, cRTip::Init
    void kill_tip_widgets(); // @ 0x4489e0
    void update_tip(); // @ 0x448c40, cRTip::AI

    int active;                         // +0x00
    int previous_outer_owner;           // +0x04
    TipData* definition;                // +0x08
    FrontendWidget* widget_main;        // +0x0c
    FrontendWidget* widget_ok;          // +0x10
    FrontendWidget* widget_disable;     // +0x14
    float dismiss_progress;             // +0x18
    float dismiss_step;                 // +0x1c
};
typedef Tip TipSlot;

class TipManager : public BodBase {
public:
    void initialize_tip_manager(); // @ 0x448cf0, cRTipManager::Init
    void uninit_tips(); // @ 0x448d10, cRTipManager::UnInitTips
    Tip* enqueue_tip_message(TipData* definition, int hide_disable_button); // @ 0x448d30, cRTipManager::TipNew
    void update_tip_manager(); // @ 0x448d80, cRTipManager::AI

    Tip tips[3]; // +0x38
};

typedef char TipData_must_be_0x14[(sizeof(TipData) == 0x14) ? 1 : -1];
typedef char Tip_must_be_0x20[(sizeof(Tip) == 0x20) ? 1 : -1];
typedef char TipManager_must_be_0x98[
    (sizeof(TipManager) == 0x98) ? 1 : -1];

#endif
