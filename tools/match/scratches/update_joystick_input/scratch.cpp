// update_joystick_input @ 0x44b570 (cdecl)

#include "direct_input_view.h"

int update_input_controller_slot_button_axes(int slot, int buttons, float axis_x, float axis_y);

int update_joystick_input()
{
    int slot = 0;
    if (g_joystick_count > 0) {
        DirectInputDevice** device_ref = g_joystick_devices;
        while (slot < g_joystick_count) {
            if (*device_ref == 0)
                break;

            if ((*device_ref)->Poll() < 0) {
                while (g_joystick_devices[slot]->Acquire() == 0x8007001e) {
                }
                return 0;
            }

            DIJOYSTATE2 state;
            int result = (*device_ref)->GetDeviceState(sizeof(state), &state);
            if (result < 0)
                return result;

            float axis_x = (float)state.lX * 0.001f;
            if (axis_x > 1000.0f) {
                axis_x = 1000.0f;
            } else if (axis_x <= -1000.0f) {
                axis_x = -1000.0f;
            }

            float axis_y = (float)state.lY * 0.001f;
            if (axis_y > 1000.0f) {
                axis_y = 1000.0f;
            } else if (axis_y <= -1000.0f) {
                axis_y = -1000.0f;
            }

            unsigned char first_button = state.rgbButtons[12];
            int buttons = 0;
            if ((first_button & 0x80) != 0)
                buttons = 1;
            if ((state.rgbButtons[14] & 0x80) != 0)
                buttons |= 2;
            if ((state.rgbButtons[15] & 0x80) != 0)
                buttons |= 4;
            if ((state.rgbButtons[13] & 0x80) != 0)
                buttons |= 8;
            if ((state.rgbButtons[2] & 0x80) != 0)
                buttons |= 0x10;
            if ((state.rgbButtons[3] & 0x80) != 0)
                buttons |= 0x20;
            if ((state.rgbButtons[1] & 0x80) != 0)
                buttons |= 0x40;
            if ((state.rgbButtons[0] & 0x80) != 0)
                buttons |= 0x80;
            if ((state.rgbButtons[6] & 0x80) != 0)
                buttons |= 0x100;
            if ((state.rgbButtons[7] & 0x80) != 0)
                buttons |= 0x200;
            if ((state.rgbButtons[4] & 0x80) != 0)
                buttons |= 0x1000;
            if ((state.rgbButtons[5] & 0x80) != 0)
                buttons |= 0x2000;
            if ((state.rgbButtons[11] & 0x80) != 0)
                buttons |= 0x400;
            if ((state.rgbButtons[8] & 0x80) != 0)
                buttons |= 0x800;

            update_input_controller_slot_button_axes(slot, buttons, axis_x, axis_y);
            update_input_controller_slot_button_axes(1, buttons, axis_x, axis_y);

            ++slot;
            ++device_ref;
        }
    }
    return 0;
}
