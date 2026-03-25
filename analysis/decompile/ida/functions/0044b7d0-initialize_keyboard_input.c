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
  result = DirectInput8Create(v1, 2048, &riidltf, &dword_777B2C[136], 0);
  if ( result >= 0 )
  {
    result = (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)dword_777B2C[136] + 12))(
               dword_777B2C[136],
               &unk_49B010,
               &dword_777B2C[137],
               0);
    if ( result >= 0 )
    {
      result = (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_777B2C[137] + 44))(dword_777B2C[137], &unk_49B504);
      if ( result >= 0 )
      {
        result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)dword_777B2C[137] + 52))(dword_777B2C[137], hWnd, 5);
        if ( result >= 0 )
        {
          (*(void (__stdcall **)(int))(*(_DWORD *)dword_777B2C[137] + 28))(dword_777B2C[137]);
          memset(&dword_777B2C[8], 0, 0x100u);
          memset(&dword_777B2C[72], 0, 0x100u);
          return 0;
        }
      }
    }
  }
  return result;
}

