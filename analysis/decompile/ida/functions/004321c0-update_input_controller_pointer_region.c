/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_input_controller_pointer_region @ 0x4321c0 */
/* selector: update_input_controller_pointer_region */

// Refreshes one global input-controller slot from a screen-space pointer region: stores the active bounds, optionally warps the pixel cursor into that region, updates normalized authored 640x480 coordinates, and latches the per-slot button bits.
void __cdecl sub_4321C0(
        int a1,
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
  MEMORY[0x5088A0][a1] = a2;
  MEMORY[0x508890][a1] = a3;
  MEMORY[0x5088A8][a1] = a4;
  MEMORY[0x508898][a1] = a5;
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
      click_mouse_screen(a1, v14, v13);
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
  v15 = 56 * a1;
  *(float *)(v15 + 5256016) = (double)(640 * (v14 - a2)) / (double)(a4 - a2);
  *(float *)(v15 + 5256020) = (double)(480 * (v13 - a3)) / (double)(a5 - a3);
  *(float *)(v15 + 5256024) = (float)a8;
  if ( a9 )
  {
    v16 = MEMORY[0x503344][14 * a1];
    BYTE1(v16) |= 0x40u;
    MEMORY[0x503344][14 * a1] = v16;
  }
  if ( a10 )
  {
    v17 = MEMORY[0x503344][14 * a1];
    BYTE1(v17) |= 0x80u;
    MEMORY[0x503344][14 * a1] = v17;
  }
  if ( a11 )
    MEMORY[0x503344][14 * a1] |= 0x100000u;
  if ( *(float *)&MEMORY[0x503350][14 * a1] >= 1.0 )
  {
    if ( *(float *)&MEMORY[0x503350][14 * a1] <= 632.0 )
      v18 = *(float *)&MEMORY[0x503350][14 * a1];
    else
      v18 = 632.0;
  }
  else
  {
    v18 = 1.0;
  }
  *(float *)&MEMORY[0x503350][14 * a1] = v18;
  if ( *(float *)&MEMORY[0x503354][14 * a1] >= 1.0 )
  {
    if ( *(float *)&MEMORY[0x503354][14 * a1] <= 472.0 )
      MEMORY[0x503354][14 * a1] = MEMORY[0x503354][14 * a1];
    else
      MEMORY[0x503354][14 * a1] = 1139539968;
  }
  else
  {
    MEMORY[0x503354][14 * a1] = 1065353216;
  }
}

