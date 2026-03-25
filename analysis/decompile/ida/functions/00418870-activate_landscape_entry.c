/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: activate_landscape_entry @ 0x418870 */
/* selector: activate_landscape_entry */

// Binds one cached landscape entry into the shared backdrop manager, applies its texture or model handles, chooses the random variant flag, and copies its fog color into the global render state.
_DWORD *__thiscall sub_418870(char *this, int a2)
{
  int v2; // eax
  int v4; // ebp
  char *v5; // edi
  char *v6; // esi
  char *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  _DWORD *v11; // edi
  _DWORD *result; // eax
  char v13; // [esp+Ch] [ebp-8h]
  int v14; // [esp+10h] [ebp-4h]

  v2 = *((_DWORD *)MEMORY[0x4DF904] + 119190);
  if ( v2 == 7 )
  {
    v13 = 0;
  }
  else if ( v2 == 1 )
  {
    v13 = (double)next_math_random_value() * 0.000030517578 <= 0.5;
  }
  else
  {
    v13 = unk_4DF9BC & 1;
  }
  v4 = 0;
  v14 = 0;
  v5 = this + 292 * a2;
  v6 = this + 4;
  do
  {
    if ( *((_DWORD *)v5 + 428) == -1 )
    {
      *(_DWORD *)v6 &= ~0x20u;
      set_bod_object((_DWORD *)v6 - 1, 0);
    }
    else
    {
      v7 = (char *)MEMORY[0x4DF904] + 3973724;
      if ( (*(_DWORD *)v6 & 0x200) != 0 )
      {
        report_errorf(aListAddafter);
      }
      else
      {
        *((_DWORD *)v6 + 1) = v7;
        *((_DWORD *)v6 + 2) = *((_DWORD *)v7 + 3);
        *((_DWORD *)v7 + 3) = v6 - 4;
        v8 = *((_DWORD *)v6 + 2);
        if ( v8 )
          *(_DWORD *)(v8 + 8) = v6 - 4;
        v9 = *(_DWORD *)v6;
        BYTE1(v9) = BYTE1(*(_DWORD *)v6) | 2;
        *(_DWORD *)v6 = v9;
      }
      *((_DWORD *)v6 + 31) = 1;
      v10 = *(_DWORD *)v6;
      LOBYTE(v10) = *(_DWORD *)v6 | 0x20;
      *(_DWORD *)v6 = v10;
      set_bod_object((_DWORD *)v6 - 1, *((_DWORD *)MEMORY[0x4DF904] + 47 * *((_DWORD *)v5 + 428) + 74635));
      *((float *)v6 + 33) = *(float *)(*((_DWORD *)v6 + 8) + 184) - *(float *)(*((_DWORD *)v6 + 8) + 172);
      set_matrix_identity((_DWORD *)v6 + 13);
      *((float *)v6 + 27) = ((double)v14 - 0.5) * *((float *)v6 + 33);
      *((_DWORD *)v6 + 34) = (char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904];
    }
    ++v4;
    v6 += 144;
    v14 = v4;
  }
  while ( v4 < 10 );
  change_backdrop((int)MEMORY[0x4DF904] + 322576, (int)(v5 + 1444), v13);
  set_border_justify_centre((_DWORD *)MEMORY[0x4DF904] + 723, 0);
  v11 = v5 + 1716;
  result = (char *)MEMORY[0x4DF904] + 20;
  *((_DWORD *)MEMORY[0x4DF904] + 5) = *v11;
  result[1] = v11[1];
  result[2] = v11[2];
  result[3] = v11[3];
  return result;
}

