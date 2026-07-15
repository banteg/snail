/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: configure_input_controller_axis_range_callback @ 0x44b4e0 */
/* selector: configure_input_controller_axis_range_callback */

// DirectInput object-enumeration callback that applies the native `[-1000, 1000]` range property to each axis object on one enumerated input controller.
int __stdcall configure_input_controller_axis_range_callback(DIDEVICEOBJECTINSTANCEA *instance, void *context)
{
  int v2; // edi
  IDirectInputDevice8A **i; // esi
  struct DIPROPRANGE range; // [esp+8h] [ebp-18h] BYREF

  if ( (instance->dwType & 3) == 0 )
    return 1;
  range.diph.dwObj = instance->dwType;
  v2 = 0;
  range.diph.dwSize = 24;
  range.diph.dwHeaderSize = 16;
  range.diph.dwHow = 2;
  range.lMin = -1000;
  range.lMax = 1000;
  if ( g_joystick_count <= 0 )
    return 1;
  for ( i = g_joystick_devices; (*i)->lpVtbl->SetProperty(*i, (void *)4, &range.diph) >= 0; ++i )
  {
    if ( ++v2 >= g_joystick_count )
      return 1;
  }
  return 0;
}
