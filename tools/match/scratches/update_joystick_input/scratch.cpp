// update_joystick_input @ 0x44b570 (cdecl)

#include "direct_input_view.h"

struct JoystickState {
    int x;
    int y;
    int z;
    int rx;
    int ry;
    int rz;
    int slider[2];
    unsigned int pov[4];
    signed char buttons[0x110 - 0x30];
};

typedef char JoystickState_must_be_0x110[
    (sizeof(JoystickState) == 0x110) ? 1 : -1];

extern int g_joystick_count; // data_777b2c
extern DirectInputDevice* g_joystick_devices[4]; // data_777b34

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

            JoystickState state;
            int result = (*device_ref)->GetDeviceState(0x110, &state);
            if (result < 0)
                return result;

            float axis_x = (float)state.x * 0.001f;
            if (axis_x > 1000.0f) {
                axis_x = 1000.0f;
            } else if (axis_x <= -1000.0f) {
                axis_x = -1000.0f;
            }

            float axis_y = (float)state.y * 0.001f;
            if (axis_y > 1000.0f) {
                axis_y = 1000.0f;
            } else if (axis_y <= -1000.0f) {
                axis_y = -1000.0f;
            }

            unsigned char first_button = state.buttons[12];
            int buttons = 0;
            if ((first_button & 0x80) != 0)
                buttons = 1;
            if ((state.buttons[14] & 0x80) != 0)
                buttons |= 2;
            if ((state.buttons[15] & 0x80) != 0)
                buttons |= 4;
            if ((state.buttons[13] & 0x80) != 0)
                buttons |= 8;
            if ((state.buttons[2] & 0x80) != 0)
                buttons |= 0x10;
            if ((state.buttons[3] & 0x80) != 0)
                buttons |= 0x20;
            if ((state.buttons[1] & 0x80) != 0)
                buttons |= 0x40;
            if ((state.buttons[0] & 0x80) != 0)
                buttons |= 0x80;
            if ((state.buttons[6] & 0x80) != 0)
                buttons |= 0x100;
            if ((state.buttons[7] & 0x80) != 0)
                buttons |= 0x200;
            if ((state.buttons[4] & 0x80) != 0)
                buttons |= 0x1000;
            if ((state.buttons[5] & 0x80) != 0)
                buttons |= 0x2000;
            if ((state.buttons[11] & 0x80) != 0)
                buttons |= 0x400;
            if ((state.buttons[8] & 0x80) != 0)
                buttons |= 0x800;

            update_input_controller_slot_button_axes(slot, buttons, axis_x, axis_y);
            update_input_controller_slot_button_axes(1, buttons, axis_x, axis_y);

            ++slot;
            ++device_ref;
        }
    }
    return 0;
}
