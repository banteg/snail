/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: draw_font_text_instance @ 0x44a360 */
/* selector: draw_font_text_instance */

// Draws one queued font text instance by mapping each byte through the atlas slot table and submitting textured glyph quads.
char __cdecl sub_44A360(int a1)
{
  int v2; // eax
  char *v3; // ebx
  char result; // al
  int v5; // ebp
  int v6; // ecx
  int v7; // eax
  double v8; // st7
  int v9; // eax
  int v10; // edi
  int v11; // ebx
  float *v12; // eax
  int v13; // eax
  float v14; // [esp+0h] [ebp-8Ch]
  float v15; // [esp+4h] [ebp-88h]
  float v16; // [esp+20h] [ebp-6Ch]
  float v17; // [esp+20h] [ebp-6Ch]
  float v18; // [esp+24h] [ebp-68h]
  float v19; // [esp+24h] [ebp-68h]
  float v20; // [esp+40h] [ebp-4Ch]
  float v21; // [esp+40h] [ebp-4Ch]
  float v22; // [esp+54h] [ebp-38h]
  float v23; // [esp+58h] [ebp-34h]
  float v24; // [esp+5Ch] [ebp-30h]
  int v25; // [esp+60h] [ebp-2Ch]
  int v26; // [esp+64h] [ebp-28h]
  float v27; // [esp+68h] [ebp-24h]
  float v28; // [esp+6Ch] [ebp-20h]
  float v29; // [esp+70h] [ebp-1Ch]
  float v30; // [esp+70h] [ebp-1Ch]
  int v31; // [esp+74h] [ebp-18h]
  char *v32; // [esp+78h] [ebp-14h]
  int v33[4]; // [esp+7Ch] [ebp-10h] BYREF
  float v34; // [esp+90h] [ebp+4h]

  v34 = *(float *)(a1 + 4);
  v2 = *(_DWORD *)(a1 + 72);
  switch ( v2 )
  {
    case 2:
      v34 = *(float *)(a1 + 76)
          + 320.0
          - measure_font_text_width((char *)*(_DWORD *)(a1 + 68), *(_DWORD *)(a1 + 60), *(float *)(a1 + 64)) * 0.5;
      break;
    case 1:
      measure_font_text_width(*(char **)(a1 + 68), *(_DWORD *)(a1 + 60), *(float *)(a1 + 64));
      v34 = *(float *)(a1 + 76) + 320.0;
      break;
    case 3:
      v34 = *(float *)(a1 + 76)
          + 320.0
          - measure_font_text_width((char *)*(_DWORD *)(a1 + 68), *(_DWORD *)(a1 + 60), *(float *)(a1 + 64));
      break;
  }
  v3 = *(char **)(a1 + 68);
  v22 = 0.0;
  v32 = v3;
  for ( result = *v3;
        result;
        v34 = (double)(int)(__int64)unk_777704[522 * *(_DWORD *)(a1 + 60) + v5]
            * *(float *)&unk_777B14[522 * *(_DWORD *)(a1 + 60)]
            * *(float *)&unk_777B10[522 * *(_DWORD *)(a1 + 60)]
            * *(float *)(a1 + 64)
            + v34 )
  {
    v5 = font_slot_index_for_char(result);
    v6 = v5 + 522 * *(_DWORD *)(a1 + 60);
    v27 = *(float *)&unk_777304[v6];
    v25 = unk_777504[v6];
    v20 = *(float *)&unk_7772E8 + v22;
    v31 = unk_777904[v6];
    v7 = 522 * *(_DWORD *)(a1 + 60);
    v26 = unk_777B08[v7];
    v24 = *(float *)&unk_777B0C[v7];
    v8 = sine(v20);
    v29 = v8 * *(float *)(a1 + 52) + v8 * *(float *)(a1 + 52);
    v21 = v22 * 3.0 + *(float *)&unk_7772E8;
    v22 = v22 + 1.0;
    v30 = (float)(int)(__int64)(v29 + v34);
    v28 = (float)(int)(__int64)(cosine(v21) * *(float *)(a1 + 52) * 4.0 + *(float *)(a1 + 8));
    if ( v5 != 53 )
    {
      if ( *(_BYTE *)(a1 + 56) )
      {
        if ( unk_777B1C[522 * *(_DWORD *)(a1 + 60)] > 0 )
        {
          v9 = *(_DWORD *)(a1 + 60);
          v10 = 2088 * v9;
          v23 = (float)unk_777B1C[522 * v9];
          v11 = 522 * v9;
          v12 = (float *)set_color_rgba(v33, 0, 0, 0, 1061997773);
          v18 = *(float *)(v10 + 7830276) * *(float *)(a1 + 64) * *(float *)(v10 + 7830288);
          v16 = unk_777704[v11 + v5] * *(float *)(a1 + 64) * *(float *)(v10 + 7830288);
          v15 = v23 + v28;
          v14 = v23 + v30;
          draw_textured_quad_immediate(
            *((_DWORD *)&unk_7772FC + v31 + v11),
            v14,
            v15,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            v16,
            v18,
            v27,
            *(float *)&v26,
            *(float *)&v25,
            v24,
            v12,
            2,
            0.0);
          v3 = v32;
        }
      }
      v13 = 522 * *(_DWORD *)(a1 + 60);
      v19 = unk_777B04[522 * *(_DWORD *)(a1 + 60)]
          * *(float *)(a1 + 64)
          * *(float *)&unk_777B10[522 * *(_DWORD *)(a1 + 60)];
      v17 = unk_777704[v13 + v5] * *(float *)(a1 + 64) * *(float *)&unk_777B10[522 * *(_DWORD *)(a1 + 60)];
      draw_textured_quad_immediate(
        *((_DWORD *)&unk_7772FC + v31 + v13),
        v30,
        v28,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        0.0,
        v17,
        v19,
        v27,
        *(float *)&v26,
        *(float *)&v25,
        v24,
        (float *)(a1 + 108),
        1,
        0.0);
    }
    result = *++v3;
    v32 = v3;
  }
  return result;
}

