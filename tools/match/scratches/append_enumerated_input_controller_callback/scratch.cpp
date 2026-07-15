// append_enumerated_input_controller_callback @ 0x44b490 (stdcall, ret 0x8)

#include "direct_input_view.h"

int __stdcall append_enumerated_input_controller_callback(
    DIDEVICEINSTANCEA* instance,
    void* context)
{
    DirectInputDevice** out_device = &g_joystick_devices[g_joystick_count];
    ++g_joystick_count;
    if (g_joystick_input->CreateDevice(&instance->guidInstance, out_device, 0) < 0)
        return 1;
    return g_joystick_count
        < (int)(sizeof(g_joystick_devices) / sizeof(g_joystick_devices[0]));
}
