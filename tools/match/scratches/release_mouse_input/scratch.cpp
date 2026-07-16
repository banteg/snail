// release_mouse_input @ 0x44c2c0 (cdecl)

#include "direct_input_view.h"

int release_mouse_input()
{
    DirectInputDevice* device = g_mouse_device;
    if (device != 0) {
        device->Unacquire();

        device = g_mouse_device;
        if (device != 0) {
            device->Release();
            g_mouse_device = 0;
        }
    }

    DirectInput* input = g_mouse_input;
    int result = (int)input;
    if (input != 0) {
        result = input->Release();
        g_mouse_input = 0;
    }
    return result;
}
