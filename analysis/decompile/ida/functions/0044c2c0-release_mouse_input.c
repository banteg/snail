/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: release_mouse_input @ 0x44c2c0 */
/* selector: release_mouse_input */

// Releases the DirectInput mouse device and its shared DirectInput interface, clearing the global mouse-input handles.
int release_mouse_input()
{
  int result; // eax

  if ( dword_777B2C[156] )
  {
    (*(void (__stdcall **)(int))(*(_DWORD *)dword_777B2C[156] + 32))(dword_777B2C[156]);
    if ( dword_777B2C[156] )
    {
      (*(void (__stdcall **)(int))(*(_DWORD *)dword_777B2C[156] + 8))(dword_777B2C[156]);
      dword_777B2C[156] = 0;
    }
  }
  result = dword_777B2C[155];
  if ( dword_777B2C[155] )
  {
    result = (*(int (__stdcall **)(int))(*(_DWORD *)dword_777B2C[155] + 8))(dword_777B2C[155]);
    dword_777B2C[155] = 0;
  }
  return result;
}

