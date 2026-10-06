// update_input_controller_slot_button_axes @ 0x431ff0 (cdecl)

#include "input_controller_state.h"

void update_input_controller_slot_button_axes(
    int slot,
    int buttons,
    int axis_x_bits,
    int axis_y_bits)
{
    if (slot == 0) {
        g_input_controller_slot0.buttons |= buttons;
        if (g_input_controller_slot0.axis_x == 0.0f) {
            *(int*)&g_input_controller_slot0.axis_x = axis_x_bits;
        }
        if (g_input_controller_slot0.axis_y == 0.0f) {
            *(int*)&g_input_controller_slot0.axis_y = axis_y_bits;
        }
    } else {
        int slot_offset = (slot * 7) << 3;
        int* slot_buttons = (int*)((char*)g_input_slot0_buttons + slot_offset);
        int* slot_axis_x = (int*)((char*)g_input_slot0_axis_x + slot_offset);
        int* slot_axis_y = (int*)((char*)g_input_slot0_axis_y + slot_offset);
        *slot_buttons = buttons;
        *slot_axis_x = axis_x_bits;
        *slot_axis_y = axis_y_bits;

        float slot0_axis_x = g_input_controller_slot0.axis_x;
        float centered;
        if (slot0_axis_x > 0.150000006f) {
            centered = (slot0_axis_x - 0.150000006f) * 1.17647064f;
        } else {
            if (slot0_axis_x > -0.150000006f) {
                centered = 0.0f;
            } else {
                centered = (-slot0_axis_x - 0.150000006f) * -1.17647064f;
            }
        }

        int slot1_buttons = g_input_controller_slot1.buttons;
        g_input_controller_slot1.authored_x = (centered + 1.0f) * 320.0f;
        if ((buttons & 0xf0) != 0) {
            slot1_buttons |= INPUT_BUTTON_PRIMARY;
        } else {
            slot1_buttons &= ~INPUT_BUTTON_PRIMARY;
        }
        g_input_controller_slot1.buttons = slot1_buttons;
    }
}
