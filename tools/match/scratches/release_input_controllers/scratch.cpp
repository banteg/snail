// release_input_controllers @ 0x44b770 (cdecl)

#include "direct_input_view.h"

extern int g_joystick_count; // data_777b2c
extern DirectInput* volatile g_joystick_input; // data_777b30
extern DirectInputDevice* volatile g_joystick_devices[4]; // data_777b34

int release_input_controllers()
{
    int index = 0;
    if (g_joystick_count > 0) {
        DirectInputDevice* volatile* device_ref = g_joystick_devices;
        do {
            DirectInputDevice* device = *device_ref;
            if (device != 0)
                device->Unacquire();

            device = *device_ref;
            if (device != 0) {
                device->Release();
                *device_ref = 0;
            }

            ++index;
            ++device_ref;
        } while (index < g_joystick_count);
    }

    DirectInput* input = g_joystick_input;
    int result = (int)input;
    if (input != 0) {
        result = input->Release();
        g_joystick_input = 0;
    }
    return result;
}
