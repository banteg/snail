/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_keyboard_input @ 0x44b7d0 */
/* selector: initialize_keyboard_input */

// Initializes the DirectInput keyboard device, sets its data format/cooperative level, acquires it, and clears the previous/current key-state buffers.
int __cdecl initialize_keyboard_input(HWND hWnd)
{
  int v1; // eax
  int result; // eax

  ((void (__stdcall *)(HWND, int))GetWindowLongA)(hWnd, -6);
  release_input_controllers();
  v1 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
  result = DirectInput8Create(v1, 2048, &g_directinput8_iid, &g_keyboard_input, 0);
  if ( result >= 0 )
  {
    result = g_keyboard_input->lpVtbl->CreateDevice(
               g_keyboard_input,
               (const DirectInputGuid *)&g_directinput_keyboard_guid,
               &g_keyboard_device,
               nullptr);
    if ( result >= 0 )
    {
      result = g_keyboard_device->lpVtbl->SetDataFormat(g_keyboard_device, &g_directinput_keyboard_data_format);
      if ( result >= 0 )
      {
        result = g_keyboard_device->lpVtbl->SetCooperativeLevel(g_keyboard_device, hWnd, 5);
        if ( result >= 0 )
        {
          g_keyboard_device->lpVtbl->Acquire(g_keyboard_device);
          memset(g_keyboard_previous_state, 0, sizeof(g_keyboard_previous_state));
          memset(g_keyboard_current_state, 0, sizeof(g_keyboard_current_state));
          return 0;
        }
      }
    }
  }
  return result;
}
