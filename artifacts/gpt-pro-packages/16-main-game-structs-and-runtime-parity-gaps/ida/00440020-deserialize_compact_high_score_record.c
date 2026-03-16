/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: deserialize_compact_high_score_record @ 0x440020 */
/* selector: deserialize_compact_high_score_record */

// Validates one compact ScoreA/B/C record checksum, copies its scalar fields, name, and replay samples into the expanded cRSubHighScore entry, and marks the entry active.
char __thiscall sub_440020(char *this, int a2)
{
  int v4; // edx
  int v5; // eax
  _WORD *v6; // ecx
  _WORD *v7; // edx
  int v8; // ecx
  int v9; // eax
  _WORD *v10; // edx
  _WORD *v11; // ecx
  int v12; // ecx
  int v13; // eax
  int v14; // ebp
  _WORD *v15; // ecx

  if ( *(_DWORD *)(a2 + 40) == ((*(_DWORD *)(a2 + 4) * *(_DWORD *)(a2 + 4)) ^ 0xDEADBABE) )
  {
    *((_DWORD *)this + 27) = *(_DWORD *)(a2 + 116);
    *((_DWORD *)this + 10) = *(_DWORD *)(a2 + 44);
    *((_DWORD *)this + 11) = *(_DWORD *)(a2 + 48);
    *((_DWORD *)this + 18) = *(_DWORD *)(a2 + 72);
    *((_DWORD *)this + 13) = *(_DWORD *)(a2 + 84);
    sub_44E5B0(this + 84, (char *)(a2 + 92));
    *((_DWORD *)this + 1) = *(_DWORD *)(a2 + 4);
    qmemcpy(this + 8, (const void *)(a2 + 8), 0x1Cu);
    *((_DWORD *)this + 19) = *(_DWORD *)(a2 + 76);
    *((_DWORD *)this + 20) = *(_DWORD *)(a2 + 80);
    *((_DWORD *)this + 32428) = *(_DWORD *)(a2 + 120);
    *((_DWORD *)this + 32429) = *(_DWORD *)(a2 + 124);
    *((_DWORD *)this + 9) = *(_DWORD *)(a2 + 36);
    *((_DWORD *)this + 26) = *(_DWORD *)(a2 + 112);
    *((_DWORD *)this + 32430) = *(_DWORD *)(a2 + 128);
    *((_DWORD *)this + 32431) = *(_DWORD *)(a2 + 132);
    *((_DWORD *)this + 14) = *(_DWORD *)(a2 + 56);
    *((_DWORD *)this + 15) = *(_DWORD *)(a2 + 60);
    v4 = *((_DWORD *)this + 27);
    *((_DWORD *)this + 16) = *(_DWORD *)(a2 + 64);
    v5 = 0;
    *((_DWORD *)this + 17) = *(_DWORD *)(a2 + 68);
    v6 = (_WORD *)(a2 + 136);
    if ( v4 > 0 )
    {
      v7 = this + 112;
      do
      {
        ++v5;
        *v7 = *v6++;
        v7 += 3;
      }
      while ( v5 < *((_DWORD *)this + 27) );
    }
    v8 = *((_DWORD *)this + 27);
    v9 = 0;
    v10 = (_WORD *)(a2 + 2 * v8 + 136);
    if ( v8 > 0 )
    {
      v11 = this + 114;
      do
      {
        ++v9;
        *v11 = *v10;
        v11 += 3;
        ++v10;
      }
      while ( v9 < *((_DWORD *)this + 27) );
    }
    v12 = *((_DWORD *)this + 27);
    v13 = 0;
    v14 = a2 + 4 * v12 + 136;
    if ( v12 > 0 )
    {
      v15 = this + 116;
      do
      {
        *v15 = *(unsigned __int8 *)(v13 + v14);
        ++v13;
        v15 += 3;
      }
      while ( v13 < *((_DWORD *)this + 27) );
    }
    *(_DWORD *)this = 1;
    return 1;
  }
  else
  {
    *(_DWORD *)this = 0;
    return 0;
  }
}

