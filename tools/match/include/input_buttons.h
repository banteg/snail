// Shared controller/button word vocabulary. These bits are produced by the
// pointer and controller adapters, copied through InputControllerSlot into
// InputState, and consumed as the primary/secondary action edges throughout
// the front end and player controller.
#ifndef INPUT_BUTTONS_H
#define INPUT_BUTTONS_H

enum InputButtonFlag {
    INPUT_BUTTON_PRIMARY = 0x4000,
    INPUT_BUTTON_SECONDARY = 0x8000,
};

#endif
