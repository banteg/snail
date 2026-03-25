/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_keyboard_input @ 0x44bb60 */
/* selector: release_keyboard_input */

// Releases the DirectInput keyboard device and its shared DirectInput interface, clearing the global keyboard-input handles.
int release_mouse_input()
{
  int result; // eax

  if ( dword_777B2C[137] )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_777B2C[137] + 32))(dword_777B2C[137]);
    if ( dword_777B2C[137] )
    {
      (*(void (__stdcall **)(int))(*(_DWORD *)dword_777B2C[137] + 8))(dword_777B2C[137]);
      dword_777B2C[137] = 0;
    }
  }
  result = dword_777B2C[136];
  if ( dword_777B2C[136] )
  {
    result = (*(int (__stdcall **)(int))(*(_DWORD *)dword_777B2C[136] + 8))(dword_777B2C[136]);
    dword_777B2C[136] = 0;
  }
  return result;
}

