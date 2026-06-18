// release_keyboard_input @ 0x44bb60 (cdecl)

#include "direct_input_view.h"

extern DirectInput* g_keyboard_input; // data_777d4c
extern DirectInputDevice* g_keyboard_device; // data_777d50

int release_keyboard_input()
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
    int result = (int)input;
    if (input != 0) {
        result = input->Release();
        g_keyboard_input = 0;
    }
    return result;
}
