// copy_active_input_controller_state @ 0x4320f0 (cdecl, ret)

#include "input_controller_state.h"

float* copy_active_input_controller_state(
    int slot_index,
    int* out_buttons,
    float* out_axis_x,
    float* out_axis_y,
    float* out_authored_x,
    float* out_authored_y,
    float* out_pointer_value,
    float* out_pointer_x,
    float* out_pointer_y)
{
    if (slot_index == 0) {
        *out_buttons = g_input_controller_slot0.buttons;
        *out_axis_x = g_input_controller_slot0.axis_x;
        *out_axis_y = g_input_controller_slot0.axis_y;
        *out_authored_x = g_input_controller_slot0.authored_x;
        *out_authored_y = g_input_controller_slot0.authored_y;
        *out_pointer_value = g_input_controller_slot0.pointer_value;
        *out_pointer_x = g_input_controller_slot0.pointer_x;
        *out_pointer_y = g_input_controller_slot0.pointer_y;
        return out_pointer_value;
    } else {
        *out_buttons = g_input_controller_slot1.buttons;
        *out_axis_x = g_input_controller_slot1.axis_x;
        *out_axis_y = g_input_controller_slot1.axis_y;
        *out_authored_x = g_input_controller_slot1.authored_x;
        *out_authored_y = g_input_controller_slot1.authored_y;
        *out_pointer_value = g_input_controller_slot1.pointer_value;
        *out_pointer_x = g_input_controller_slot1.pointer_x;
        *out_pointer_y = g_input_controller_slot1.pointer_y;
    }
    return out_pointer_value;
}
