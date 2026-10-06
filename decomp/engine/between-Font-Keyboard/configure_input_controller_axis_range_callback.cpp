// configure_input_controller_axis_range_callback @ 0x44b4e0 (stdcall, ret 0x8)

#include "direct_input_view.h"

int __stdcall configure_input_controller_axis_range_callback(
    DIDEVICEOBJECTINSTANCEA* instance,
    void* context)
{
    unsigned int object_type = instance->dwType;
    if ((object_type & 3) == 0)
        return 1;

    DIPROPRANGE property;
    property.diph.dwSize = sizeof(property);
    property.diph.dwHeaderSize = sizeof(property.diph);
    property.diph.dwObj = object_type;
    property.diph.dwHow = 2;
    property.lMin = -1000;
    property.lMax = 1000;

    int index = 0;
    if (g_joystick_count > 0) {
        DirectInputDevice** device_ref = g_joystick_devices;
        while (index < g_joystick_count) {
            if ((*device_ref)->SetProperty((void*)4, &property.diph) < 0)
                return 0;
            ++index;
            ++device_ref;
        }
    }
    return 1;
}
