// Embedded OK-button state used by border text input widgets.
#ifndef INPUT_OK_STATE_H
#define INPUT_OK_STATE_H

#include "frontend_widget.h"

class InputOkState {
public:
    void update_input_ok(); // @ 0x4034d0, Android cRInputOK::AI()
    void initialize_input_ok(); // @ 0x403560, Android cRInputOK::Init()

    char unknown_00[0x1c];
    cRBorder* source_widget; // +0x1c
    cRBorder* ok_widget; // +0x20
};

// Android retains the authored name and the same complete 0x24-byte owner.
typedef InputOkState cRInputOK;

typedef char InputOkState_must_be_0x24[
    (sizeof(InputOkState) == 0x24) ? 1 : -1];

#endif
