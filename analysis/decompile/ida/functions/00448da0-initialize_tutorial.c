/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_tutorial @ 0x448da0 */
/* selector: initialize_tutorial */

char __thiscall sub_448DA0(_DWORD *this)
{
  char *v1; // eax
  int v2; // ecx
  int v3; // eax

  *this = 0;
  v1 = (char *)MEMORY[0x4DF904] + 476696;
  *(this + 3) = (char *)MEMORY[0x4DF904] + 476696;
  *((_DWORD *)v1 + 19) |= (unsigned int)&unk_600000;
  v2 = *(this + 3);
  v3 = *(_DWORD *)(v2 + 76);
  LOBYTE(v3) = v3 & 0xFD;
  *(_DWORD *)(v2 + 76) = v3;
  return v3;
}

