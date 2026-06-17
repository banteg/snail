/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_input_controllers @ 0x44b770 */
/* selector: release_input_controllers */

// Releases every enumerated DirectInput controller device plus the shared DirectInput interface and clears the global controller list.
int release_input_controllers()
{
  int v0; // edi
  int *v1; // esi
  int result; // eax

  v0 = 0;
  if ( g_joystick_count > 0 )
  {
    v1 = g_joystick_devices;
    do
    {
      if ( *v1 )
        (*(void (__stdcall **)(int))(*(_DWORD *)*v1 + 32))(*v1);
      if ( *v1 )
      {
        (*(void (__stdcall **)(int))(*(_DWORD *)*v1 + 8))(*v1);
        *v1 = 0;
      }
      ++v0;
      ++v1;
    }
    while ( v0 < g_joystick_count );
  }
  result = g_joystick_input;
  if ( g_joystick_input )
  {
    result = (*(int (__stdcall **)(int))(*(_DWORD *)g_joystick_input + 8))(g_joystick_input);
    g_joystick_input = 0;
  }
  return result;
}
