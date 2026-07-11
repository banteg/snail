/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_mouse_input @ 0x44c310 */
/* selector: initialize_mouse_input */

int __cdecl initialize_mouse_input(int window_handle)
{
  int v1; // eax
  int result; // eax

  g_mouse_live_x[0] = g_authored_view_width * 0.5;
  g_hide_system_cursor_flag = 1;
  g_mouse_live_y[0] = g_authored_view_height * 0.5;
  v1 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
  result = DirectInput8Create(v1, 2048, &g_directinput8_iid, &g_mouse_input, 0);
  if ( result >= 0 )
  {
    result = (*(int (__stdcall **)(void *, void *, void **, _DWORD))(*(_DWORD *)g_mouse_input + 12))(
               g_mouse_input,
               &g_directinput_mouse_guid,
               &g_mouse_device,
               0);
    if ( result >= 0 )
    {
      result = (*(int (__stdcall **)(void *, void *))(*(_DWORD *)g_mouse_device + 44))(
                 g_mouse_device,
                 &g_directinput_mouse_data_format);
      if ( result >= 0 )
      {
        (*(void (__stdcall **)(void *, int, int))(*(_DWORD *)g_mouse_device + 52))(g_mouse_device, window_handle, 4);
        (*(void (__stdcall **)(void *))(*(_DWORD *)g_mouse_device + 28))(g_mouse_device);
        return 0;
      }
    }
  }
  return result;
}

