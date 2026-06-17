/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_keyboard_input @ 0x44b7d0 */
/* selector: initialize_keyboard_input */

int __cdecl initialize_keyboard_input(int hWnd)
{
  int v1; // eax
  int result; // eax

  ((void (__stdcall *)(int, int))GetWindowLongA)(hWnd, -6);
  release_input_controllers();
  v1 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
  result = DirectInput8Create(v1, 2048, &g_directinput8_iid, &g_keyboard_input, 0);
  if ( result >= 0 )
  {
    result = (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)g_keyboard_input + 12))(
               g_keyboard_input,
               &g_directinput_keyboard_guid,
               &g_keyboard_device,
               0);
    if ( result >= 0 )
    {
      result = (*(int (__stdcall **)(int, void *))(*(_DWORD *)g_keyboard_device + 44))(g_keyboard_device, &g_directinput_keyboard_data_format);
      if ( result >= 0 )
      {
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)g_keyboard_device + 52))(g_keyboard_device, hWnd, 5);
        if ( result >= 0 )
        {
          (*(void (__stdcall **)(int))(*(_DWORD *)g_keyboard_device + 28))(g_keyboard_device);
          memset(g_keyboard_previous_state, 0, 0x100u);
          memset(g_keyboard_current_state, 0, 0x100u);
          return 0;
        }
      }
    }
  }
  return result;
}
