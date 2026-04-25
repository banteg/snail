/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: serialize_compact_high_score_record @ 0x440170 */
/* selector: serialize_compact_high_score_record */

// Compacts one active cRSubHighScore entry into the ScoreA/B/C on-disk record format, including checksum, name, and variable replay payload arrays.
int __thiscall sub_440170(char *this, int a2)
{
  int v3; // eax
  int v4; // eax
  _WORD *v5; // edx
  _WORD *v6; // ecx
  int v7; // ecx
  int v8; // eax
  _WORD *v9; // edx
  _WORD *v10; // ecx
  int v11; // ecx
  int v12; // eax
  int v13; // edi
  char *v14; // esi
  char v15; // cl
  int result; // eax

  v3 = *((_DWORD *)this + 27);
  *(_DWORD *)this = 1;
  *(_DWORD *)(a2 + 116) = v3;
  *(_DWORD *)(a2 + 44) = *((_DWORD *)this + 10);
  *(_DWORD *)(a2 + 48) = *((_DWORD *)this + 11);
  *(_DWORD *)(a2 + 72) = *((_DWORD *)this + 18);
  *(_DWORD *)(a2 + 84) = *((_DWORD *)this + 13);
  rstrcpy_checked_ascii((char *)(a2 + 92), this + 84);
  qmemcpy((void *)(a2 + 8), this + 8, 0x1Cu);
  *(_DWORD *)(a2 + 76) = *((_DWORD *)this + 19);
  *(_DWORD *)(a2 + 80) = *((_DWORD *)this + 20);
  *(_DWORD *)(a2 + 120) = *((_DWORD *)this + 32428);
  *(_DWORD *)(a2 + 124) = *((_DWORD *)this + 32429);
  *(_DWORD *)(a2 + 36) = *((_DWORD *)this + 9);
  *(_DWORD *)(a2 + 4) = *((_DWORD *)this + 1);
  *(_DWORD *)(a2 + 40) = (*((_DWORD *)this + 1) * *((_DWORD *)this + 1)) ^ 0xDEADBABE;
  *(_DWORD *)(a2 + 112) = *((_DWORD *)this + 26);
  *(_DWORD *)(a2 + 128) = *((_DWORD *)this + 32430);
  *(_DWORD *)(a2 + 132) = *((_DWORD *)this + 32431);
  *(_DWORD *)(a2 + 56) = *((_DWORD *)this + 14);
  *(_DWORD *)(a2 + 60) = *((_DWORD *)this + 15);
  *(_DWORD *)(a2 + 64) = *((_DWORD *)this + 16);
  *(_DWORD *)(a2 + 68) = *((_DWORD *)this + 17);
  v4 = 0;
  v5 = (_WORD *)(a2 + 136);
  if ( *((int *)this + 27) > 0 )
  {
    v6 = this + 112;
    do
    {
      ++v4;
      *v5 = *v6;
      v6 += 3;
      ++v5;
    }
    while ( v4 < *((_DWORD *)this + 27) );
  }
  v7 = *((_DWORD *)this + 27);
  v8 = 0;
  v9 = (_WORD *)(a2 + 2 * v7 + 136);
  if ( v7 > 0 )
  {
    v10 = this + 114;
    do
    {
      ++v8;
      *v9 = *v10;
      v10 += 3;
      ++v9;
    }
    while ( v8 < *((_DWORD *)this + 27) );
  }
  v11 = *((_DWORD *)this + 27);
  v12 = 0;
  v13 = a2 + 4 * v11 + 136;
  if ( v11 > 0 )
  {
    v14 = this + 116;
    do
    {
      v15 = *v14;
      v14 += 6;
      *(_BYTE *)(v13 + v12++) = v15;
    }
    while ( v12 < *((_DWORD *)this + 27) );
  }
  result = 5 * *((_DWORD *)this + 27) + 136;
  *(_DWORD *)a2 = result;
  return result;
}

