/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: try_enter_track_attachment_from_swept_motion @ 0x42c770 */
/* selector: try_enter_track_attachment_from_swept_motion */

// Scans the authored runtime attachment samples against the player's swept motion box, seeds the shared scratch follow-state block when a candidate hit survives the local bounds tests, and immediately runs one follow update to validate the candidate. Windows `cdb` confirmed shipped `ARCADE007` HalfPipe play reaches the live follow-state path driven by this entry family. Raw BN plus the checked-in IDA export now also show the helper itself does not directly clear `player + 0x41d` before control returns to the caller's secondary-slot gate.
void __thiscall sub_42C770(_DWORD *this, float a2, float a3, float a4, float a5, float a6, float a7, int a8)
{
  int v9; // esi
  int v10; // esi
  int i; // ebp
  float *v12; // ecx
  double v13; // st7
  float *v14; // ecx
  double v15; // st7
  float v16; // [esp+14h] [ebp-60h] BYREF
  float v17; // [esp+18h] [ebp-5Ch]
  float v18; // [esp+1Ch] [ebp-58h]
  float v19; // [esp+20h] [ebp-54h]
  float v20; // [esp+24h] [ebp-50h]
  float v21; // [esp+28h] [ebp-4Ch]
  float v22; // [esp+2Ch] [ebp-48h]
  float v23; // [esp+30h] [ebp-44h]
  float v24; // [esp+34h] [ebp-40h]
  float v25; // [esp+38h] [ebp-3Ch]
  float v26; // [esp+3Ch] [ebp-38h]
  float v27; // [esp+40h] [ebp-34h]
  float v28; // [esp+44h] [ebp-30h] BYREF
  float v29; // [esp+48h] [ebp-2Ch]
  float v30; // [esp+4Ch] [ebp-28h]
  float v31; // [esp+54h] [ebp-20h]
  float v32; // [esp+58h] [ebp-1Ch]
  float v33; // [esp+60h] [ebp-14h]
  float v34; // [esp+64h] [ebp-10h]
  float v35; // [esp+6Ch] [ebp-8h]
  float v36; // [esp+70h] [ebp-4h]

  v9 = *(this + 17);
  v19 = *(float *)(a8 + 16);
  v10 = v9 - 1;
  v20 = *(float *)(a8 + 20);
  v21 = *(float *)(a8 + 24);
  if ( v10 >= 0 )
  {
    for ( i = 168 * v10; ; i -= 168 )
    {
      v12 = (float *)(i + *(this + 23));
      if ( v12[5] > 0.0 )
      {
        v13 = v19 + v12[12];
        v31 = v20 + v12[13];
        v32 = v21 + v12[14];
        v22 = a2 - v13;
        v16 = v22;
        v23 = a3 - v31;
        v17 = v23;
        v24 = a4 - v32;
        v18 = v24;
        rotate_vector_by_matrix(&v16, v12 + 16);
        if ( (double)(*(this + 21) / -2) - 0.30000001 < v16
          && (double)(*(this + 21) / 2) + 0.30000001 > v16
          && v17 >= -0.2
          && v18 > 0.0 )
        {
          v14 = (float *)(*(this + 23) + i);
          if ( v18 < (double)v14[35] )
          {
            v15 = v19 + v14[12];
            v35 = v20 + v14[13];
            v36 = v21 + v14[14];
            v33 = a3 + a6;
            v34 = a4 + a7;
            v25 = a5 + a2 - v15;
            v28 = v25;
            v26 = v33 - v35;
            v29 = v26;
            v27 = v34 - v36;
            v30 = v27;
            rotate_vector_by_matrix(&v28, v14 + 16);
            if ( v29 <= 0.001 )
              break;
          }
        }
      }
      if ( --v10 < 0 )
        return;
    }
    *((_BYTE *)&loc_430199 + (_DWORD)MEMORY[0x4DF904]) = 0;
    start_squidge_y((int)uninit_thanks_screen + (_DWORD)MEMORY[0x4DF904], *((float *)MEMORY[0x4DF904] + 1097828));
    *((_BYTE *)&loc_430100 + (_DWORD)MEMORY[0x4DF904]) = 1;
    *((_DWORD *)MEMORY[0x4DF904] + 1097793) = this;
    *((_DWORD *)MEMORY[0x4DF904] + 1097794) = a8;
    *((_DWORD *)MEMORY[0x4DF904] + 1097795) = v10;
    *((float *)MEMORY[0x4DF904] + 1097796) = v18;
    *((_DWORD *)MEMORY[0x4DF904] + 1097797) = 0;
    *((float *)MEMORY[0x4DF904] + 1097594) = v17;
    *((_DWORD *)MEMORY[0x4DF904] + 1097828) = 0;
    *((_DWORD *)MEMORY[0x4DF904] + 1097806) = (char *)&loc_42FD7C + (_DWORD)MEMORY[0x4DF904];
    *(_DWORD *)(*((_DWORD *)MEMORY[0x4DF904] + 1097793) + 152) = *(int *)((char *)&unk_64118C
                                                                        + (_DWORD)MEMORY[0x4DF904]
                                                                        + 244 * get_track_cell_row_index((_DWORD *)a8));
    *((_DWORD *)MEMORY[0x4DF904] + 1097799) = 0;
    *(_DWORD *)((char *)&loc_430118 + (_DWORD)MEMORY[0x4DF904]) = 0;
    update_track_attachment_follow_state(
      (char *)&loc_430100 + (_DWORD)MEMORY[0x4DF904],
      *((float *)MEMORY[0x4DF904] + 1097829),
      (float *)MEMORY[0x4DF904] + 1097593,
      (int)MEMORY[0x4DF904] + 4391308);
  }
}

