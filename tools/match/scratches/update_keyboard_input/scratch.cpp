// update_keyboard_input @ 0x44b870 (cdecl)

#include "direct_input_view.h"

extern "C" void* memcpy(void* destination, const void* source, unsigned int count);
extern "C" void* memset(void* destination, int value, unsigned int count);

unsigned char is_key_down(int key_code);
int set_input_controller_slot0_button_axes(int buttons, float axis_x, float axis_y);

extern DirectInputDevice* g_keyboard_device; // data_777d50
extern unsigned char g_keyboard_previous_state[0x100]; // data_777b4c
extern unsigned char g_keyboard_current_state[0x100]; // data_777c4c

int update_keyboard_input()
{
    DirectInputDevice* device = g_keyboard_device;
    if (device != 0) {
        memcpy(g_keyboard_previous_state, g_keyboard_current_state, 0x100);
        memset(g_keyboard_current_state, 0, 0x100);

        if (device->GetDeviceState(0x100, g_keyboard_current_state) < 0) {
            int result = g_keyboard_device->Acquire();
            while (result == 0x8007001e)
                result = g_keyboard_device->Acquire();

            if (result == 0x80070005 || result == 0x8007000c) {
                memset(g_keyboard_current_state, 0, 0x100);
                memset(g_keyboard_previous_state, 0, 0x100);
                return 0;
            }
        } else {
            int buttons = 0;
            float axis_x = 0.0f;
            float axis_y = 0.0f;

            if (is_key_down(0xc8)) {
                buttons = 1;
                axis_y = -1.0f;
            }
            if (is_key_down(0xd0)) {
                buttons |= 2;
                axis_y = 1.0f;
            }
            if (is_key_down(0xcb)) {
                buttons |= 4;
                axis_x = -1.0f;
            }
            if (is_key_down(0xcd)) {
                buttons |= 8;
                axis_x = 1.0f;
            }
            if (is_key_down(0x1d))
                buttons |= 0x10;
            if (is_key_down(0x2c))
                buttons |= 0x100;
            if (is_key_down(0x2e))
                buttons |= 0x200;
            if (is_key_down(0x1f))
                buttons |= 0x80;
            if (is_key_down(0x2d))
                buttons |= 0x40;
            if (is_key_down(0x38))
                buttons |= 0x4000000;
            if (is_key_down(0x38))
                buttons |= 0x20;
            if (is_key_down(0x2c))
                buttons |= 0x20000;
            if (is_key_down(0x2e))
                buttons |= 0x1000000;
            if (is_key_down(0x39))
                buttons |= 0x80000;
            if (is_key_down(0x3c))
                buttons |= 0x400;
            if (is_key_down(0x39))
                buttons |= 0x2000;
            if (is_key_down(0x11))
                buttons |= 0x400000;
            if (is_key_down(0x2d))
                buttons |= 0x40000;
            if (is_key_down(0x1f))
                buttons |= 0x200000;
            if (is_key_down(0x12))
                buttons |= 0x800000;
            if (is_key_down(0x1d))
                buttons |= 0x10000;
            if (is_key_down(0x2a))
                buttons |= 0x2000000;

            set_input_controller_slot0_button_axes(buttons, axis_x, axis_y);
        }
    }
    return 0;
}
