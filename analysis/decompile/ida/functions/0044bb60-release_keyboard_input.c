/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_keyboard_input @ 0x44bb60 */
/* selector: release_keyboard_input */

// Releases the DirectInput keyboard device and its shared DirectInput interface, clearing the global keyboard-input handles.
void __cdecl release_keyboard_input()
{
  if ( g_keyboard_device != nullptr )
  {
    g_keyboard_device->lpVtbl->Unacquire(g_keyboard_device);
    if ( g_keyboard_device != nullptr )
    {
      g_keyboard_device->lpVtbl->Release(g_keyboard_device);
      g_keyboard_device = nullptr;
    }
  }
  if ( g_keyboard_input != nullptr )
  {
    g_keyboard_input->lpVtbl->Release(g_keyboard_input);
    g_keyboard_input = nullptr;
  }
}
