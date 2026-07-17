/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_controller_pointer_region @ 0x4321c0 */
/* selector: update_input_controller_pointer_region */

// Refreshes one 0x20-byte InputControllerSlot payload at the proved 0x38-byte RShell stride from a screen-space pointer region: stores the active bounds, mutates the incoming X/Y coordinates while optionally warping the cursor into that region, updates authored 640x480 coordinates, and latches the per-slot button bits. The sole caller ignores the incidental comparison residue, proving the native contract is void.
void __cdecl update_input_controller_pointer_region(
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
  int v13; // ebx
  int v14; // esi
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  double v18; // st7

  v13 = y;
  v14 = x;
  g_input_region_left[slot] = left;
  g_input_region_top[slot] = top;
  g_input_region_right[slot] = right;
  g_input_region_bottom[slot] = bottom;
  if ( x < left || x >= right || y < top || y >= bottom )
  {
    if ( !capture_when_outside || force_clamp )
    {
      if ( x < left )
        v14 = left;
      if ( v14 >= right )
        v14 = right - 1;
      if ( y < top )
        v13 = top;
      if ( v13 >= bottom )
        v13 = bottom - 1;
      click_mouse_screen(slot, v14, v13);
      set_hide_system_cursor_flag(1);
    }
    else
    {
      set_hide_system_cursor_flag(0);
    }
  }
  else
  {
    set_hide_system_cursor_flag(1);
  }
  v15 = 56 * slot;
  *(float *)(v15 + 5256016) = (double)(640 * (v14 - left)) / (double)(right - left);
  *(float *)(v15 + 5256020) = (double)(480 * (v13 - top)) / (double)(bottom - top);
  *(float *)(v15 + 5256024) = (float)pointer_value;
  if ( button_a )
  {
    v16 = *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot);
    BYTE1(v16) |= 0x40u;
    *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot) = v16;
  }
  if ( button_b )
  {
    v17 = *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot);
    BYTE1(v17) |= 0x80u;
    *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot) = v17;
  }
  if ( button_c )
    *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot) |= 0x100000u;
  if ( *(&g_input_controller_slot0.authored_x + 14 * slot) >= 1.0 )
  {
    if ( *(&g_input_controller_slot0.authored_x + 14 * slot) <= 632.0 )
      v18 = *(&g_input_controller_slot0.authored_x + 14 * slot);
    else
      v18 = 632.0;
  }
  else
  {
    v18 = 1.0;
  }
  *(&g_input_controller_slot0.authored_x + 14 * slot) = v18;
  if ( *(&g_input_controller_slot0.authored_y + 14 * slot) >= 1.0 )
  {
    if ( *(&g_input_controller_slot0.authored_y + 14 * slot) <= 472.0 )
      *(&g_input_controller_slot0.authored_y + 14 * slot) = *(&g_input_controller_slot0.authored_y + 14 * slot);
    else
      *((_DWORD *)&g_input_controller_slot0.authored_y + 14 * slot) = 1139539968;
  }
  else
  {
    *((_DWORD *)&g_input_controller_slot0.authored_y + 14 * slot) = 1065353216;
  }
}
