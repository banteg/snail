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
        *out_buttons = g_input_slot0_buttons[0];
        *out_axis_x = g_input_slot0_axis_x[0];
        *out_axis_y = g_input_slot0_axis_y[0];
        *out_authored_x = g_input_slot0_authored_x[0];
        *out_authored_y = g_input_slot0_authored_y[0];
        *out_pointer_value = g_input_slot0_pointer_value[0];
        *out_pointer_x = g_input_slot0_pointer_x[0];
        *out_pointer_y = g_input_slot0_pointer_y[0];
        return out_pointer_value;
    } else {
        *out_buttons = g_input_slot0_buttons[14];
        *out_axis_x = g_input_slot0_axis_x[14];
        *out_axis_y = g_input_slot0_axis_y[14];
        *out_authored_x = g_input_slot0_authored_x[14];
        *out_authored_y = g_input_slot0_authored_y[14];
        *out_pointer_value = g_input_slot0_pointer_value[14];
        *out_pointer_x = g_input_slot0_pointer_x[14];
        *out_pointer_y = g_input_slot0_pointer_y[14];
    }
    return out_pointer_value;
}
