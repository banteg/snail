/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enumerate_input_controllers @ 0x44b3c0 */
/* selector: enumerate_input_controllers */

int __cdecl enumerate_input_controllers(int window_handle, int *out_count)
{
  int v2; // eax
  int result; // eax
  int v4; // ebx
  IDirectInputDevice8A **i; // esi

  g_joystick_count = 0;
  *out_count = 0;
  v2 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
  result = DirectInput8Create(v2, 2048, &g_directinput8_iid, &g_joystick_input, 0);
  if ( result >= 0 )
  {
    result = g_joystick_input->lpVtbl->EnumDevices(
               g_joystick_input,
               4,
               append_enumerated_input_controller_callback,
               nullptr,
               1);
    if ( result >= 0 )
    {
      *out_count = g_joystick_count;
      if ( g_joystick_devices[0] && (v4 = 0, g_joystick_count > 0) )
      {
        for ( i = g_joystick_devices; ; ++i )
        {
          result = (*i)->lpVtbl->SetDataFormat(*i, &g_directinput_joystick_data_format);
          if ( result < 0 )
            break;
          result = (*i)->lpVtbl->SetCooperativeLevel(*i, window_handle, 5);
          if ( result < 0 )
            break;
          result = (*i)->lpVtbl->EnumObjects(
                     *i,
                     configure_input_controller_axis_range_callback,
                     (void *)window_handle,
                     0);
          if ( result < 0 )
            break;
          if ( ++v4 >= g_joystick_count )
            return 0;
        }
      }
      else
      {
        return 0;
      }
    }
  }
  return result;
}
