// update_input_controller_pointer_region @ 0x4321c0 (cdecl)

#include "input_controller_state.h"

void set_hide_system_cursor_flag(int hidden); // @ 0x44c050
void* click_mouse_screen(int slot, int x, int y); // @ 0x44c060

void update_input_controller_pointer_region(
    int slot,
    int left,
    int top,
    int right,
    int bottom,
    int x,
    int y,
    int pointer_value,
    char button_a,
    char button_b,
    char button_c,
    char capture_when_outside,
    char force_clamp)
{
    g_input_region_left[slot] = left;
    g_input_region_top[slot] = top;
    g_input_region_right[slot] = right;
    g_input_region_bottom[slot] = bottom;

    if (x >= left && x < right && y >= top && y < bottom) {
        set_hide_system_cursor_flag(1);
    } else {
        if (capture_when_outside == 0 || force_clamp != 0) {
            if (x < left) {
                x = left;
            }
            if (x >= right) {
                x = right - 1;
            }
            if (y < top) {
                y = top;
            }
            if (y >= bottom) {
                y = bottom - 1;
            }
            click_mouse_screen(slot, x, y);
            set_hide_system_cursor_flag(1);
        } else {
            set_hide_system_cursor_flag(0);
        }
    }

    g_input_controller_slots[slot].authored_x =
        (float)((x - left) * 640) / (float)(right - left);
    g_input_controller_slots[slot].authored_y =
        (float)((y - top) * 480) / (float)(bottom - top);
    g_input_controller_slots[slot].pointer_value = (float)pointer_value;

    if (button_a != 0) {
        g_input_controller_slots[slot].buttons |= 0x4000;
    }
    if (button_b != 0) {
        g_input_controller_slots[slot].buttons |= 0x8000;
    }
    if (button_c != 0) {
        g_input_controller_slots[slot].buttons |= 0x100000;
    }

    float clamped_x;
    if (g_input_controller_slots[slot].authored_x < 1.0f) {
        clamped_x = 1.0f;
    } else if (g_input_controller_slots[slot].authored_x > 632.0f) {
        clamped_x = 632.0f;
    } else {
        clamped_x = g_input_controller_slots[slot].authored_x;
    }
    g_input_controller_slots[slot].authored_x = clamped_x;

    float clamped_y;
    if (g_input_controller_slots[slot].authored_y < 1.0f) {
        clamped_y = 1.0f;
    } else if (g_input_controller_slots[slot].authored_y > 472.0f) {
        clamped_y = 472.0f;
    } else {
        clamped_y = g_input_controller_slots[slot].authored_y;
    }
    g_input_controller_slots[slot].authored_y = clamped_y;
}
