// Shared tooltip state embedded in FrontendWidget at +0x28c. The widget
// itself is forward-declared so scratches can reuse this layout without taking
// the full FrontendWidget ABI.
#ifndef TOOLTIP_STATE_H
#define TOOLTIP_STATE_H

class FrontendWidget;

class TooltipState {
public:
    int reset_tooltip(); // @ 0x403be0
    void update_tooltip(); // @ 0x403c20

    int field_00; // +0x00
    int state; // +0x04
    unsigned int mode_flags; // +0x08
    FrontendWidget* owner_widget; // +0x0c
    float delay_progress; // +0x10
    float delay_step; // +0x14
    FrontendWidget* tooltip_widget; // +0x18
    char unknown_01c[0x38 - 0x1c];
    FrontendWidget* owner_widget_38; // +0x38
    char unknown_03c[0x40 - 0x03c];
};

typedef char TooltipState_must_be_0x40[
    (sizeof(TooltipState) == 0x40) ? 1 : -1];

#endif
