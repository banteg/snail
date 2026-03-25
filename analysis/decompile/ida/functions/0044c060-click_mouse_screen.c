/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: click_mouse_screen @ 0x44c060 */
/* selector: click_mouse_screen */

void *__cdecl click_mouse_screen(int a1, int X, int Y)
{
  double v3; // st7
  _DWORD *v4; // ecx
  void *result; // eax
  float Xa; // [esp+14h] [ebp+8h]

  if ( !unk_4DFAF4
    && is_mouse_captured((char *)MEMORY[0x4DF904] + 656) == 1
    && !a1
    && !unk_4B7654
    && ((int (*)(void))GetActiveWindow)() == MEMORY[0x4DFAF0] )
  {
    ((void (__stdcall *)(int, int))SetCursorPos)(X, Y);
  }
  v3 = (double)X;
  v4 = MEMORY[0x4DF904];
  dword_777B2C[a1 + 148] = X;
  dword_777B2C[a1 + 146] = Y;
  *(float *)&dword_777B2C[a1 + 139] = v3;
  Xa = (float)Y;
  *(float *)&dword_777B2C[a1 + 141] = Xa;
  *(float *)(v4[163] + 96) = v3;
  result = MEMORY[0x4DF904];
  *(float *)(*((_DWORD *)MEMORY[0x4DF904] + 163) + 100) = Xa;
  return result;
}

