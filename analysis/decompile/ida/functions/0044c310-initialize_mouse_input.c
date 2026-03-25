/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_mouse_input @ 0x44c310 */
/* selector: initialize_mouse_input */

int __cdecl initialize_mouse_input(int a1)
{
  int v1; // eax
  int result; // eax

  *(float *)&dword_777B2C[139] = unk_4DF85C * 0.5;
  LOBYTE(dword_777B2C[145]) = 1;
  *(float *)&dword_777B2C[141] = unk_4B7760 * 0.5;
  v1 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
  result = DirectInput8Create(v1, 2048, &riidltf, &dword_777B2C[155], 0);
  if ( result >= 0 )
  {
    result = (*(int (__stdcall **)(int, void *, int *, _DWORD))(*(_DWORD *)dword_777B2C[155] + 12))(
               dword_777B2C[155],
               &unk_49B020,
               &dword_777B2C[156],
               0);
    if ( result >= 0 )
    {
      result = (*(int (__stdcall **)(int, void *))(*(_DWORD *)dword_777B2C[156] + 44))(dword_777B2C[156], &unk_49B70C);
      if ( result >= 0 )
      {
        (*(void (__stdcall **)(int, int, int))(*(_DWORD *)dword_777B2C[156] + 52))(dword_777B2C[156], a1, 4);
        (*(void (__stdcall **)(int))(*(_DWORD *)dword_777B2C[156] + 28))(dword_777B2C[156]);
        return 0;
      }
    }
  }
  return result;
}

