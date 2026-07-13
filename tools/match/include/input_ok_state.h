// Embedded OK-button state used by border text input widgets.
#ifndef INPUT_OK_STATE_H
#define INPUT_OK_STATE_H

#include "frontend_widget.h"

class InputOkState {
public:
    FrontendWidget* update_input_ok(); // @ 0x4034d0
    FrontendWidget* initialize_input_ok(); // @ 0x403560

    char unknown_00[0x1c];
    FrontendWidget* source_widget; // +0x1c
    FrontendWidget* ok_widget; // +0x20
};

typedef char InputOkState_must_be_0x24[
    (sizeof(InputOkState) == 0x24) ? 1 : -1];

#endif
