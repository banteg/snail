/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_survival_high_score @ 0x417780 */
/* selector: add_survival_high_score */

// Attempts to insert one completed challenge or survival run into the ordered top-10 bank, mirrors the pending entry into the challenge bank overlay, and arms the high-score entry screen when the run places. Cross-port Android and iOS symbols match this helper to `cRSubHighScore::AddSurvival()`.
int __thiscall sub_417780(_DWORD *this, _DWORD *a2)
{
  int result; // eax
  _DWORD *i; // ecx
  int v5; // ebx
  _DWORD *v6; // ebp
  void *v7; // edi
  _DWORD *v8; // ebx

  result = 0;
  a2[15] = 1;
  a2[16] = 0;
  a2[17] = 0;
  qmemcpy(this + 2367538, a2, 0x1FAC0u);
  qmemcpy(this + 2399970, a2, 0x1FAC0u);
  for ( i = this + 356755; a2[1] <= *i; i += 32432 )
  {
    if ( ++result >= 10 )
      return result;
  }
  v5 = 10;
  v6 = this + 681074;
  do
  {
    v7 = v6;
    v6 -= 32432;
    qmemcpy(v7, v6, 0x1FAC0u);
    v6[32448] = v5--;
  }
  while ( v5 > result );
  v8 = this + 32432 * result;
  qmemcpy(v8 + 356754, a2, 0x1FAC0u);
  v8[356769] = 1;
  v8[356770] = result;
  *((_DWORD *)MEMORY[0x4DF904] + 110) = 20;
  *((_BYTE *)MEMORY[0x4DF904] + 781) = 1;
  if ( result != -1 )
  {
    a2[15] = 1;
    v8[356769] = 1;
    *(int *)((char *)&byte_6FFAE0 + (_DWORD)MEMORY[0x4DF904]) = (int)(this + 356754);
    *((_DWORD *)MEMORY[0x4DF904] + 196) = result;
    result = (int)MEMORY[0x4DF904];
    *((_DWORD *)MEMORY[0x4DF904] + 197) = 1;
  }
  return result;
}

