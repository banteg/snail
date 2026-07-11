/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_mouse_input @ 0x44c2c0 */
/* selector: release_mouse_input */

// Releases the DirectInput mouse device and its shared DirectInput interface, clearing the global mouse-input handles.
int __cdecl release_mouse_input()
{
  int result; // eax

  if ( g_mouse_device )
  {
    (*(void (__stdcall **)(void *))(*(_DWORD *)g_mouse_device + 32))(g_mouse_device);
    if ( g_mouse_device )
    {
      (*(void (__stdcall **)(void *))(*(_DWORD *)g_mouse_device + 8))(g_mouse_device);
      g_mouse_device = nullptr;
    }
  }
  result = (int)g_mouse_input;
  if ( g_mouse_input )
  {
    result = (*(int (__stdcall **)(void *))(*(_DWORD *)g_mouse_input + 8))(g_mouse_input);
    g_mouse_input = nullptr;
  }
  return result;
}

