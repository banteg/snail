/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: activate_landscape_entry @ 0x418870 */
/* selector: activate_landscape_entry */

// Selects one cached landscape script, activates up to ten repeated 0x90-byte landscape BOD slices for its object index, chooses the backdrop variant flag, and copies the script fog color into global render state.
uint8_t *__thiscall activate_landscape_entry(char *this, int a2)
{
  int32_t level_mode; // eax
  int v4; // ebp
  char *v5; // edi
  char *v6; // esi
  uint8_t *v7; // eax
  int v8; // eax
  int v9; // eax
  int v10; // eax
  _DWORD *v11; // edi
  uint8_t *result; // eax
  char v13; // [esp+Ch] [ebp-8h]
  int v14; // [esp+10h] [ebp-4h]

  level_mode = g_game_base->subgame.level_mode;
  if ( level_mode == 7 )
  {
    v13 = 0;
  }
  else if ( level_mode == 1 )
  {
    v13 = (double)next_math_random_value() * 0.000030517578 <= 0.5;
  }
  else
  {
    v13 = g_runtime_config.landscape_backdrop_variant_selector & 1;
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
      set_bod_object((BodBase *)(v6 - 4), nullptr);
    }
    else
    {
      v7 = &g_game_base->subgame.unknown_000044[3496960];
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
      set_bod_object((BodBase *)(v6 - 4), *(Object **)&g_game_base->unknown_044100[188 * *((_DWORD *)v5 + 428) + 19756]);
      *((float *)v6 + 33) = *(float *)(*((_DWORD *)v6 + 8) + 184) - *(float *)(*((_DWORD *)v6 + 8) + 172);
      set_matrix_identity((TransformMatrix *)(v6 + 52));
      *((float *)v6 + 27) = ((double)v14 - 0.5) * *((float *)v6 + 33);
      *((_DWORD *)v6 + 34) = (char *)&g_player_block + (_DWORD)g_game_base;
    }
    ++v4;
    v6 += 144;
    v14 = v4;
  }
  while ( v4 < 10 );
  change_backdrop((int)&g_game_base->unknown_044100[43792], (int)(v5 + 1444), v13);
  set_border_justify_centre(&g_game_base->border_manager, 0.0);
  v11 = v5 + 1716;
  result = &g_game_base->unknown_000000[20];
  *(_DWORD *)&g_game_base->unknown_000000[20] = *v11;
  *((_DWORD *)result + 1) = v11[1];
  *((_DWORD *)result + 2) = v11[2];
  *((_DWORD *)result + 3) = v11[3];
  return result;
}
