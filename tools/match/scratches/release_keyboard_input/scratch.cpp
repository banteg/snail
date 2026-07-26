// release_keyboard_input @ 0x44bb60 (cdecl)

#include "direct_input_view.h"

void release_keyboard_input()
{
    DirectInputDevice* device = g_keyboard_device;
    if (device != 0) {
        device->Unacquire();

        device = g_keyboard_device;
        if (device != 0) {
            device->Release();
            g_keyboard_device = 0;
        }
    }

    DirectInput* input = g_keyboard_input;
    if (input != 0) {
        input->Release();
        g_keyboard_input = 0;
    }
}
