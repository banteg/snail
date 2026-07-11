// set_input_controller_slot0_button_axes @ 0x431fd0 (cdecl, ret)

#include "input_controller_state.h"

int set_input_controller_slot0_button_axes(int buttons, float axis_x, float axis_y)
{
    g_input_slot0_buttons[0] = buttons;
    g_input_slot0_axis_x[0] = axis_x;
    g_input_slot0_axis_y[0] = axis_y;
    return buttons;
}
