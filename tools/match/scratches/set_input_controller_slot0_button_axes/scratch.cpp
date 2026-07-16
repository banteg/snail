// set_input_controller_slot0_button_axes @ 0x431fd0 (cdecl, ret)

#include "input_controller_state.h"

int set_input_controller_slot0_button_axes(int buttons, float axis_x, float axis_y)
{
    g_input_controller_slot0.buttons = buttons;
    g_input_controller_slot0.axis_x = axis_x;
    g_input_controller_slot0.axis_y = axis_y;
    return buttons;
}
