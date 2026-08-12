// Authored cRToolTip owner embedded in cRBorder at +0x28c. The widget
// itself is forward-declared so scratches can reuse this layout without taking
// the full FrontendWidget ABI. Binary Ninja and the shared C analysis headers
// use the semantic FrontendWidgetTooltip spelling for this 0x40-byte subobject.
#ifndef TOOLTIP_STATE_H
#define TOOLTIP_STATE_H

#include "border_fwd.h"

class cRToolTip {
public:
    void ReSet(); // @ 0x403be0
    void AI(); // @ 0x403c20

    int field_00; // +0x00
    int state; // +0x04
    unsigned int mode_flags; // +0x08
    cRBorder* owner_widget; // +0x0c, borrowed enclosing widget backlink
    float delay_progress; // +0x10
    float delay_step; // +0x14
    cRBorder* tooltip_widget; // +0x18, cRBorderManager-owned live widget handle
    char unknown_01c[0x38 - 0x1c];
    cRBorder* owner_widget_38; // +0x38, second borrowed widget backlink
    char unknown_03c[0x40 - 0x03c];
};

typedef cRToolTip FrontendWidgetTooltip;
typedef char FrontendWidgetTooltip_must_be_0x40[
    (sizeof(cRToolTip) == 0x40) ? 1 : -1];

#endif
