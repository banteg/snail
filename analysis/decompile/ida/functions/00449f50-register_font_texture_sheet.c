/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: register_font_texture_sheet @ 0x449f50 */
/* selector: register_font_texture_sheet */

// Loads one FONT-MENU-HOVER atlas, scans row-0 white delimiters and the column-0 height marker, and registers per-slot metrics and texture refs.
int __cdecl sub_449F50(char *FileName, int a2, int a3, float a4)
{
  int v4; // ebx
  _BYTE *v5; // esi
  char v6; // cl
  int i; // eax
  int v8; // eax
  int v9; // edi
  int v10; // ebp
  int v11; // eax
  int v12; // edx
  float *v13; // eax
  int v14; // ecx
  int v15; // edi
  int v16; // eax
  _DWORD *v17; // eax
  int *v18; // eax
  int v19; // ecx
  int v20; // eax
  int v22; // [esp+10h] [ebp-210h]
  int v23; // [esp+14h] [ebp-20Ch]
  float v24; // [esp+14h] [ebp-20Ch]
  float v25; // [esp+18h] [ebp-208h]
  int v26; // [esp+1Ch] [ebp-204h]
  _BYTE v27[256]; // [esp+20h] [ebp-200h] BYREF
  _BYTE v28[256]; // [esp+120h] [ebp-100h] BYREF

  v4 = 0;
  if ( unk_777B20 == 1 )
    report_errorf(aTooManyFontsRf);
  v5 = load_file_bytes(FileName, nullptr);
  if ( *((_WORD *)v5 + 6) == 2048 )
  {
    v6 = *FileName;
    for ( i = 0; v6 != 46; ++i )
    {
      v27[i] = v6;
      v28[i] = v6;
      v6 = FileName[i + 1];
    }
    v27[i] = 48;
    v28[i] = 49;
    v8 = i + 1;
    v4 = 960;
    v28[v8] = 46;
    v27[v8++] = 46;
    v28[v8] = 116;
    v27[v8++] = 116;
    v28[v8] = 103;
    v27[v8++] = 103;
    v28[v8] = 97;
    v27[v8++] = 97;
    v28[v8] = 0;
    v27[v8] = 0;
  }
  v9 = 0;
  v10 = -1;
  v26 = 0;
  v23 = -1;
  v22 = 0;
  if ( *((_WORD *)v5 + 6) )
  {
    do
    {
      v11 = sub_44E780((int)v5, v9, 0);
      v12 = unk_777B20;
      if ( v11 == 0xFFFFFF )
      {
        v13 = (float *)(4 * (v26 + 522 * unk_777B20));
        v14 = v9 - v10;
        v13[1957313] = (float)v23;
        v25 = (double)(v9 - v10) + 0.5;
        v13[1957057] = v25 / (double)*((unsigned __int16 *)v5 + 6);
        v10 = 0;
        v24 = (double)v22 + 0.5;
        v13[1957185] = v24 / (double)*((unsigned __int16 *)v5 + 6);
        *(int *)((char *)unk_777904 + (_DWORD)v13) = 0;
        if ( *((_WORD *)v5 + 6) == 2048 )
        {
          if ( v14 <= v4 )
          {
            v13[1957057] = v25 * 0.0009765625;
            v13[1957185] = v24 / (double)(*((_WORD *)v5 + 6) >> 1);
            *(int *)((char *)unk_777904 + (_DWORD)v13) = 0;
          }
          else
          {
            v13[1957057] = ((double)(v14 - v4) + 0.5) * 0.0009765625;
            v13[1957185] = ((double)(v9 - v4) + 0.5) / (double)(*((_WORD *)v5 + 6) >> 1);
            *(int *)((char *)unk_777904 + (_DWORD)v13) = 1;
          }
        }
        if ( ++v26 == 128 )
        {
          report_errorf(aTooManyFontLet);
          v12 = unk_777B20;
        }
      }
      ++v10;
      ++v9;
      v23 = v10;
      v22 = v9;
    }
    while ( v9 < *((unsigned __int16 *)v5 + 6) );
  }
  else
  {
    v12 = unk_777B20;
  }
  v15 = 1;
  if ( *((_WORD *)v5 + 7) > 1u )
  {
    while ( sub_44E780((int)v5, 0, v15) != 0xFFFFFF )
    {
      if ( ++v15 >= *((unsigned __int16 *)v5 + 7) )
      {
        v12 = unk_777B20;
        goto LABEL_23;
      }
    }
    v12 = unk_777B20;
    unk_777B04[522 * unk_777B20] = (float)v15;
  }
LABEL_23:
  v16 = 2088 * v12;
  *(float *)(v16 + 7830280) = 3.0 / (double)(*((unsigned __int16 *)v5 + 7) - 1);
  *(float *)(v16 + 7830284) = *(float *)(v16 + 7830276) / (double)(*((unsigned __int16 *)v5 + 7) - 1);
  unk_7772F8[v16 / 4u] = v26;
  unk_777B1C[v16 / 4u] = a2;
  if ( *((_WORD *)v5 + 6) == 2048 )
  {
    v17 = (_DWORD *)get_or_create_texture_ref(&dword_4B7790, v27, 0, 0);
    *((_DWORD *)&unk_7772FC + 522 * unk_777B20) = v17;
    *v17 |= 0x420u;
    v18 = (int *)get_or_create_texture_ref(&dword_4B7790, v28, 0, 0);
    unk_777300[522 * unk_777B20] = (int)v18;
    v19 = *v18 | 0x420;
  }
  else
  {
    v18 = (int *)get_or_create_texture_ref(&dword_4B7790, FileName, 0, 0);
    *((_DWORD *)&unk_7772FC + 522 * unk_777B20) = v18;
    v19 = *v18;
    BYTE1(v19) = BYTE1(*v18) | 4;
  }
  *v18 = v19;
  v20 = 522 * unk_777B20;
  unk_777B10[v20] = 1065353216;
  unk_777B14[v20] = a3;
  *(float *)&unk_777B18[v20] = a4;
  *(float *)(v20 * 4 + 7830276) = a4 * *(float *)(v20 * 4 + 7830276);
  free_tracked_memory((int)v5);
  return unk_777B20++;
}

