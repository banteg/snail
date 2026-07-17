/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_input_controller_pointer_authored_xy @ 0x4323a0 */
/* selector: set_input_controller_pointer_authored_xy */

// Seeds one global input-controller slot to an authored 640x480 pointer position, updates its normalized coordinates from the stored region bounds, and warps the backing OS cursor through click_mouse_screen.
void *__cdecl set_input_controller_pointer_authored_xy(int slot, float authored_x, float authored_y)
{
  int v3; // edi
  int v4; // eax
  int v5; // ecx

  v3 = g_input_region_left[slot];
  v4 = 56 * slot;
  *(float *)((char *)&g_input_controller_slot0.authored_x + v4) = authored_x;
  v5 = g_input_region_bottom[slot];
  *(float *)((char *)&g_input_controller_slot0.authored_y + v4) = authored_y;
  return click_mouse_screen(
           slot,
           (__int64)((double)(g_input_region_right[slot] - v3) * authored_x * 0.0015625 + (double)v3),
           (__int64)((double)(v5 - g_input_region_top[slot]) * authored_y * 0.0020833334
                   + (double)g_input_region_top[slot]));
}
