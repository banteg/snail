/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: configure_input_controller_axis_range_callback @ 0x44b4e0 */
/* selector: configure_input_controller_axis_range_callback */

// DirectInput object-enumeration callback that applies the native `[-1000, 1000]` range property to each axis object on one enumerated input controller.
int __stdcall sub_44B4E0(int a1, int a2)
{
  int v2; // edi
  int *i; // esi
  _DWORD v5[6]; // [esp+8h] [ebp-18h] BYREF

  if ( (*(_DWORD *)(a1 + 24) & 3) == 0 )
    return 1;
  v5[2] = *(_DWORD *)(a1 + 24);
  v2 = 0;
  v5[0] = 24;
  v5[1] = 16;
  v5[3] = 2;
  v5[4] = -1000;
  v5[5] = 1000;
  if ( g_joystick_count <= 0 )
    return 1;
  for ( i = g_joystick_devices; (*(int (__stdcall **)(int, int, _DWORD *))(*(_DWORD *)*i + 24))(*i, 4, v5) >= 0; ++i )
  {
    if ( ++v2 >= g_joystick_count )
      return 1;
  }
  return 0;
}
