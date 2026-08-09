// Authored cRTipData/cRTip/cRTipManager tutorial-message owner family.
#ifndef TIP_MANAGER_H
#define TIP_MANAGER_H

#include "bod_types.h"

class FrontendWidget;

struct cRTipData {
    unsigned int flags;        // +0x00
    float anchor_x;            // +0x04
    float layout_y;            // +0x08
    float dismiss_seconds;     // +0x0c
    char* text;                // +0x10
};
typedef cRTipData TipData;
typedef cRTipData TipMessageDefinition;

enum {
    TIP_SLOT_COUNT = 3,
};

class cRTip {
public:
    void Init(cRTipData* definition, int hide_disable_button); // @ 0x448a40
    void UnInit(); // @ 0x4489e0
    void AI(); // @ 0x448c40

    int active;                         // +0x00
    int previous_outer_owner;           // +0x04
    cRTipData* definition;              // +0x08
    FrontendWidget* widget_main;        // +0x0c
    FrontendWidget* widget_ok;          // +0x10
    FrontendWidget* widget_disable;     // +0x14
    float dismiss_progress;             // +0x18
    float dismiss_step;                 // +0x1c
};
typedef cRTip Tip;
typedef cRTip TipSlot;

class cRTipManager : public BodBase {
public:
    void Init(); // @ 0x448cf0
    void UnInitTips(); // @ 0x448d10
    cRTip* TipNew(cRTipData* definition, int hide_disable_button); // @ 0x448d30
    void AI(); // @ 0x448d80

    cRTip tips[TIP_SLOT_COUNT]; // +0x38
};

typedef cRTipManager TipManager;

typedef char cRTipData_must_be_0x14[
    (sizeof(cRTipData) == 0x14) ? 1 : -1];
typedef char cRTip_must_be_0x20[(sizeof(cRTip) == 0x20) ? 1 : -1];
typedef char cRTipManager_must_be_0x98[
    (sizeof(cRTipManager) == 0x98) ? 1 : -1];
typedef char TipData_must_be_0x14[(sizeof(TipData) == 0x14) ? 1 : -1];
typedef char Tip_must_be_0x20[(sizeof(Tip) == 0x20) ? 1 : -1];
typedef char TipManager_must_be_0x98[
    (sizeof(TipManager) == 0x98) ? 1 : -1];

#endif
