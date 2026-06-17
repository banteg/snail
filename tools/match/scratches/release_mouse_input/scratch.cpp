// release_mouse_input @ 0x44c2c0 (cdecl)

#include "direct_input_view.h"

extern DirectInput* volatile g_mouse_input; // data_777d98
extern DirectInputDevice* volatile g_mouse_device; // data_777d9c

int release_mouse_input()
{
    DirectInputDevice* device = g_mouse_device;
    if (device != 0) {
        device->vtbl->Unacquire(device);

        device = g_mouse_device;
        if (device != 0) {
            device->vtbl->Release(device);
            g_mouse_device = 0;
        }
    }

    DirectInput* input = g_mouse_input;
    int result = (int)input;
    if (input != 0) {
        result = input->vtbl->Release(input);
        g_mouse_input = 0;
    }
    return result;
}
