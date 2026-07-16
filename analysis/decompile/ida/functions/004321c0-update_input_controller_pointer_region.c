/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_controller_pointer_region @ 0x4321c0 */
/* selector: update_input_controller_pointer_region */

// Refreshes one 0x20-byte InputControllerSlot payload at the proved 0x38-byte RShell stride from a screen-space pointer region: stores the active bounds, mutates the incoming X/Y coordinates while optionally warping the cursor into that region, updates authored 640x480 coordinates, and latches the per-slot button bits. The sole caller ignores the incidental comparison residue, proving the native contract is void.
void __cdecl update_input_controller_pointer_region(
        int slot,
        int a2,
        int a3,
        int a4,
        int a5,
        int X,
        int Y,
        int a8,
        char a9,
        char a10,
        char a11,
        char a12,
        char a13)
{
  int v13; // ebx
  int v14; // esi
  int v15; // ecx
  int v16; // eax
  int v17; // eax
  double v18; // st7

  v13 = Y;
  v14 = X;
  g_input_region_left[slot] = a2;
  g_input_region_top[slot] = a3;
  g_input_region_right[slot] = a4;
  g_input_region_bottom[slot] = a5;
  if ( X < a2 || X >= a4 || Y < a3 || Y >= a5 )
  {
    if ( !a12 || a13 )
    {
      if ( X < a2 )
        v14 = a2;
      if ( v14 >= a4 )
        v14 = a4 - 1;
      if ( Y < a3 )
        v13 = a3;
      if ( v13 >= a5 )
        v13 = a5 - 1;
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
  *(float *)(v15 + 5256016) = (double)(640 * (v14 - a2)) / (double)(a4 - a2);
  *(float *)(v15 + 5256020) = (double)(480 * (v13 - a3)) / (double)(a5 - a3);
  *(float *)(v15 + 5256024) = (float)a8;
  if ( a9 )
  {
    v16 = *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot);
    BYTE1(v16) |= 0x40u;
    *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot) = v16;
  }
  if ( a10 )
  {
    v17 = *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot);
    BYTE1(v17) |= 0x80u;
    *((_DWORD *)&g_input_controller_slot0.buttons + 14 * slot) = v17;
  }
  if ( a11 )
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
