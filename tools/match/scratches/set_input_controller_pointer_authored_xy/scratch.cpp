// set_input_controller_pointer_authored_xy @ 0x4323a0 (cdecl)

#include "input_controller_state.h"

void* click_mouse_screen(int slot, int x, int y);

void* set_input_controller_pointer_authored_xy(
    int slot,
    int authored_x_bits,
    int authored_y_bits)
{
    int left = g_input_region_left[slot];
    *(int*)&input_controller_slot(slot).authored_x = authored_x_bits;
    int bottom = g_input_region_bottom[slot];
    *(int*)&input_controller_slot(slot).authored_y = authored_y_bits;
    int top = g_input_region_top[slot];
    int screen_y =
        (int)((float)(bottom - top) * (*(float*)&authored_y_bits) * 0.00208333344f
            + (float)top);
    return click_mouse_screen(
        slot,
        (int)((float)(g_input_region_right[slot] - left)
            * (*(float*)&authored_x_bits) * 0.00156250002f + (float)left),
        screen_y);
}
