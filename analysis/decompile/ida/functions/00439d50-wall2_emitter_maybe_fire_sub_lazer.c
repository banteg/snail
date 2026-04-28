/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: wall2_emitter_maybe_fire_sub_lazer @ 0x439d50 */
/* selector: wall2_emitter_maybe_fire_sub_lazer */

// Runs the Wall2-tile emitter gate from one runtime fringe object: checks the row/tile conditions, requires the active runtime row start at `game+0x74668` to be behind Goldy's live row position at `game+0x42fdec`, rolls the random gate (`< 4/100`), derives a spawn origin + normalized direction, and calls `shoot_subgoldy` which drops the projectile into the 20-slot SubLazer pool at `game + 0x356b00`.
void __thiscall sub_439D50(int this)
{
  void *v2; // ecx
  char v3; // al
  double v4; // st7
  float v5; // ecx
  int v6; // edx
  double v7; // st7
  float v8; // edx
  double v9; // st7
  double v10; // st7
  _DWORD *v11; // edi
  _DWORD *v12; // ecx
  int v13[2]; // [esp+4h] [ebp-34h] BYREF
  float v14; // [esp+Ch] [ebp-2Ch]
  float v15[2]; // [esp+10h] [ebp-28h] BYREF
  float v16; // [esp+18h] [ebp-20h]
  float v17; // [esp+1Ch] [ebp-1Ch]
  int v18; // [esp+20h] [ebp-18h]
  float v19; // [esp+24h] [ebp-14h]
  float v20[4]; // [esp+28h] [ebp-10h] BYREF

  if ( (*(_DWORD *)(this + 64) & 0x2000) != 0 )
  {
    v2 = MEMORY[0x4DF904];
    if ( !*((_BYTE *)MEMORY[0x4DF904] + 476705) )
    {
      v3 = *(_BYTE *)(this + 60);
      switch ( v3 )
      {
        case 14:
          if ( (double)*((int *)MEMORY[0x4DF904] + 119194) >= *((float *)MEMORY[0x4DF904] + 1097595) )
            goto LABEL_9;
          if ( random_float_below(100.0) < 4.0 )
          {
            v4 = *(float *)(this + 20) + 8.0;
            v5 = *(float *)(this + 24);
            v15[0] = *(float *)(this + 16);
            v6 = *(_DWORD *)(this + 64) >> 8;
            *(float *)&v18 = v4;
            v17 = v15[0];
            *(_QWORD *)v13 = v6 & 0xF;
            v19 = v5;
            LODWORD(v15[1]) = v18;
            v16 = v5;
            v15[0] = (double)*(__int64 *)v13 * 0.5 + v15[0];
            v7 = random_signed_float_below(3.0);
            v2 = MEMORY[0x4DF904];
            v8 = *((float *)MEMORY[0x4DF904] + 1097594);
            v9 = v7 + 8.0 + *((float *)MEMORY[0x4DF904] + 1097595);
            v20[0] = *((float *)MEMORY[0x4DF904] + 1097593);
            v20[1] = v8;
            v17 = v20[0] - v15[0];
            *(float *)v13 = v17;
            *(float *)&v18 = v8 - *(float *)&v18;
            v10 = v9 - v16;
            v13[1] = v18;
            v19 = v10;
            v14 = v19;
            if ( v10 >= -4.0 )
              goto LABEL_9;
            normalize_vector((float *)v13);
            *(float *)v13 = *(float *)v13 * 0.40000001;
            *(float *)&v13[1] = *(float *)&v13[1] * 0.40000001;
            v14 = v14 * 0.40000001;
            shoot_subgoldy((_DWORD *)MEMORY[0x4DF904] + 994374, v15, v13);
          }
          v2 = MEMORY[0x4DF904];
LABEL_9:
          if ( *(float *)(this + 24) < (double)*((float *)v2 + 1100223) )
            destroy_sub_lazer_projectile(this);
          return;
        case 22:
          if ( *(float *)(this + 24) >= (double)*((float *)MEMORY[0x4DF904] + 1100223) )
            return;
          goto LABEL_13;
        case 29:
        case 30:
          if ( *(_DWORD *)(*(_DWORD *)(this + 56) + 56) == 24 )
          {
            *(float *)(this + 32) = *(float *)(this + 32) - *((float *)MEMORY[0x4DF904] + 119188) * 0.033333335;
            set_color_alpha((_DWORD *)(this + 40), 1061997773);
            v2 = MEMORY[0x4DF904];
          }
          v11 = get_track_skirt_color((int *)v2 + 119174, v20);
          v12 = (_DWORD *)((char *)&unk_6411B8
                         + (_DWORD)MEMORY[0x4DF904]
                         + 244 * get_track_cell_row_index((_DWORD *)this));
          *v12 = *v11;
          v12[1] = v11[1];
          v12[2] = v11[2];
          v12[3] = v11[3];
          if ( *((float *)MEMORY[0x4DF904] + 1100223) - ((double)*(int *)(*(_DWORD *)(this + 56) + 72) + 5.0) > *(float *)(this + 24) )
            destroy_sub_lazer_projectile(this);
          break;
        default:
          if ( *(float *)(this + 24) < (double)*((float *)MEMORY[0x4DF904] + 1100223)
            && (double)(*((_DWORD *)MEMORY[0x4DF904] + 119196) - 5) > *(float *)(this + 24) )
          {
LABEL_13:
            destroy_sub_lazer_projectile(this);
          }
          break;
      }
    }
  }
}
