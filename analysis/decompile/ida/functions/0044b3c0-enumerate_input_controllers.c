/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enumerate_input_controllers @ 0x44b3c0 */
/* selector: enumerate_input_controllers */

int __cdecl enumerate_input_controllers(int a1, _DWORD *a2)
{
  int v2; // eax
  int result; // eax
  int v4; // ebx
  int *i; // esi

  dword_777B2C[0] = 0;
  *a2 = 0;
  v2 = ((int (__stdcall *)(_DWORD))GetModuleHandleA)(0);
  result = DirectInput8Create(v2, 2048, &riidltf, &dword_777B2C[1], 0);
  if ( result >= 0 )
  {
    result = (*(int (__stdcall **)(int, int, int (__stdcall *)(int, int), _DWORD, int))(*(_DWORD *)dword_777B2C[1] + 16))(
               dword_777B2C[1],
               4,
               append_enumerated_input_controller_callback,
               0,
               1);
    if ( result >= 0 )
    {
      *a2 = dword_777B2C[0];
      if ( dword_777B2C[2] && (v4 = 0, dword_777B2C[0] > 0) )
      {
        for ( i = &dword_777B2C[2]; ; ++i )
        {
          result = (*(int (__stdcall **)(int, void *))(*(_DWORD *)*i + 44))(*i, &unk_49B2FC);
          if ( result < 0 )
            break;
          result = (*(int (__stdcall **)(int, int, int))(*(_DWORD *)*i + 52))(*i, a1, 5);
          if ( result < 0 )
            break;
          result = (*(int (__stdcall **)(int, int (__stdcall *)(int, int), int, _DWORD))(*(_DWORD *)*i + 16))(
                     *i,
                     configure_input_controller_axis_range_callback,
                     a1,
                     0);
          if ( result < 0 )
            break;
          if ( ++v4 >= dword_777B2C[0] )
            return 0;
        }
      }
      else
      {
        return 0;
      }
    }
  }
  return result;
}

