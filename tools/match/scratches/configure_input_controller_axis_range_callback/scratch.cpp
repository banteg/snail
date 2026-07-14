// configure_input_controller_axis_range_callback @ 0x44b4e0 (stdcall, ret 0x8)

#include "direct_input_view.h"

struct DirectInputObjectInstance {
    char unknown_00[0x18];
    unsigned int object_type; // +0x18
};

struct DirectInputRangeProperty {
    unsigned int size; // +0x00
    unsigned int header_size; // +0x04
    unsigned int object_id; // +0x08
    unsigned int how; // +0x0c
    int min; // +0x10
    int max; // +0x14
};

int __stdcall configure_input_controller_axis_range_callback(
    DirectInputObjectInstance* instance,
    void* context)
{
    unsigned int object_type = instance->object_type;
    if ((object_type & 3) == 0)
        return 1;

    DirectInputRangeProperty property;
    property.size = 0x18;
    property.header_size = 0x10;
    property.object_id = object_type;
    property.how = 2;
    property.min = -1000;
    property.max = 1000;

    int index = 0;
    if (g_joystick_count > 0) {
        DirectInputDevice** device_ref = g_joystick_devices;
        while (index < g_joystick_count) {
            if ((*device_ref)->SetProperty((void*)4, &property) < 0)
                return 0;
            ++index;
            ++device_ref;
        }
    }
    return 1;
}
