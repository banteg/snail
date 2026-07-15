/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_input_controllers @ 0x44b770 */
/* selector: release_input_controllers */

// Releases every enumerated DirectInput controller device plus the shared DirectInput interface and clears the global controller list.
int __cdecl release_input_controllers()
{
  int v0; // edi
  IDirectInputDevice8A **v1; // esi
  int result; // eax

  v0 = 0;
  if ( g_joystick_count > 0 )
  {
    v1 = g_joystick_devices;
    do
    {
      if ( *v1 )
        (*v1)->lpVtbl->Unacquire(*v1);
      if ( *v1 )
      {
        (*v1)->lpVtbl->Release(*v1);
        *v1 = nullptr;
      }
      ++v0;
      ++v1;
    }
    while ( v0 < g_joystick_count );
  }
  result = (int)g_joystick_input;
  if ( g_joystick_input )
  {
    result = g_joystick_input->lpVtbl->Release(g_joystick_input);
    g_joystick_input = nullptr;
  }
  return result;
}
