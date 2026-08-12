// Embedded OK-button state used by border text input widgets.
#ifndef INPUT_OK_STATE_H
#define INPUT_OK_STATE_H

#include "frontend_widget.h"
#include "input_ok_fwd.h"

class cRInputOK {
public:
    void update_input_ok(); // @ 0x4034d0, Android cRInputOK::AI()
    void initialize_input_ok(); // @ 0x403560, Android cRInputOK::Init()

    char unknown_00[0x1c];
    cRBorder* source_widget; // +0x1c
    cRBorder* ok_widget; // +0x20
};

typedef char InputOkState_must_be_0x24[
    (sizeof(cRInputOK) == 0x24) ? 1 : -1];

#endif
