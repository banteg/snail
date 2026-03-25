/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_arcade_high_score @ 0x4176a0 */
/* selector: add_arcade_high_score */

// Attempts to insert one completed postal or arcade run into the ordered top-10 bank, then arms the high-score entry screen when the run places. Cross-port Android and iOS symbols match this helper to `cRSubHighScore::AddArcade(int)`.
int __thiscall sub_4176A0(_DWORD *this, _DWORD *a2, int a3)
{
  int result; // eax
  _DWORD *i; // ecx
  int v6; // ebx
  _DWORD *v7; // edx
  void *v8; // edi
  _DWORD *v9; // edx

  result = 0;
  a2[16] = a3;
  a2[15] = 0;
  qmemcpy(this + 2367538, a2, 0x1FAC0u);
  for ( i = this + 3; a2[1] <= *i; i += 32432 )
  {
    if ( ++result >= 10 )
      return result;
  }
  v6 = 10;
  v7 = this + 324322;
  do
  {
    v8 = v7;
    v7 -= 32432;
    qmemcpy(v8, v7, 0x1FAC0u);
    v7[32448] = v6--;
  }
  while ( v6 > result );
  v9 = this + 32432 * result;
  qmemcpy(v9 + 2, a2, 0x1FAC0u);
  v9[18] = result;
  *((_DWORD *)MEMORY[0x4DF904] + 110) = 20;
  *((_BYTE *)MEMORY[0x4DF904] + 781) = 1;
  *((_DWORD *)MEMORY[0x4DF904] + 196) = result;
  result = (int)MEMORY[0x4DF904];
  *((_DWORD *)MEMORY[0x4DF904] + 197) = 0;
  return result;
}

