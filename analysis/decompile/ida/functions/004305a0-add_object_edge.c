/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: add_object_edge @ 0x4305a0 */
/* selector: add_object_edge */

void __userpurge sub_4305A0(int a1@<ecx>, double a2@<st0>, int a3, int a4, int a5)
{
  int v5; // ebp
  int v6; // edi
  int v7; // ebx
  int v9; // edx
  _DWORD *v10; // ebp
  float *v11; // edi
  float *v12; // edi
  float *v13; // ebx
  double v14; // st7
  int v15; // edx
  float *v16; // eax
  float *v17; // ecx
  double v18; // st7
  float *v19; // eax
  int v20; // ebx
  int v21; // esi
  int v22; // eax
  int v23; // eax
  float *v24; // ecx
  float *v25; // eax
  int v26; // eax
  const void *v27; // esi
  void *v28; // edi
  int v29; // [esp+10h] [ebp-38h]
  float v31; // [esp+18h] [ebp-30h] BYREF
  float v32; // [esp+1Ch] [ebp-2Ch]
  float v33; // [esp+20h] [ebp-28h]
  float v34; // [esp+24h] [ebp-24h] BYREF
  float v35; // [esp+28h] [ebp-20h]
  float v36; // [esp+2Ch] [ebp-1Ch]
  float v37[3]; // [esp+30h] [ebp-18h] BYREF
  float v38[3]; // [esp+3Ch] [ebp-Ch] BYREF
  float *v39; // [esp+50h] [ebp+8h]

  v5 = a5;
  v6 = a1;
  vector_magnitude((float *)(*(_DWORD *)(a1 + 96) + 12 * a5));
  if ( a2 < 0.89999998 )
    return;
  v7 = MEMORY[0x503318];
  v29 = 0;
  if ( MEMORY[0x503318] <= 0 )
  {
LABEL_13:
    *(_DWORD *)(MEMORY[0x503300] + 36 * v7) = 1;
    *(_DWORD *)(MEMORY[0x503300] + 36 * MEMORY[0x503318] + 4) = a3;
    *(_DWORD *)(MEMORY[0x503300] + 36 * MEMORY[0x503318] + 8) = a4;
    *(_DWORD *)(MEMORY[0x503300] + 36 * MEMORY[0x503318] + 12) = v5;
    *(_DWORD *)(MEMORY[0x503300] + 36 * MEMORY[0x503318] + 16) = 0;
    v15 = *(_DWORD *)(v6 + 56);
    v16 = (float *)(v15 + 12 * a3);
    v17 = (float *)(v15 + 12 * a4);
    v34 = *v17 - *v16;
    v35 = v17[1] - v16[1];
    v18 = v17[2] - v16[2];
    v31 = v34;
    v32 = v35;
    v36 = v18;
    v33 = v36;
    *(float *)(MEMORY[0x503300] + 36 * MEMORY[0x503318] + 32) = normalize_vector(&v31);
    v19 = (float *)(MEMORY[0x503300] + 36 * MEMORY[0x503318] + 20);
    *v19 = v31;
    v19[1] = v32;
    v19[2] = v33;
    ++MEMORY[0x503318];
    return;
  }
  v9 = *(_DWORD *)(v6 + 56);
  v39 = (float *)(v9 + 12 * a4);
  v10 = (_DWORD *)(MEMORY[0x503300] + 8);
  while ( 1 )
  {
    v11 = (float *)(v9 + 12 * *(v10 - 1));
    if ( *v11 != *v39 || v11[1] != v39[1] || v11[2] != v39[2] )
      goto LABEL_11;
    v12 = (float *)(v9 + 12 * *v10);
    v13 = (float *)(v9 + 12 * a3);
    if ( *v12 == *v13 && v12[1] == v13[1] )
    {
      v14 = v12[2];
      if ( v14 == v13[2] )
        break;
    }
    v7 = MEMORY[0x503318];
LABEL_11:
    v10 += 9;
    if ( ++v29 >= v7 )
    {
      v5 = a5;
      v6 = a1;
      goto LABEL_13;
    }
  }
  v20 = v29;
  v21 = 36 * v29;
  v22 = *(_DWORD *)(36 * v29 + MEMORY[0x503300]);
  if ( (v22 & 1) != 0 )
  {
    LOBYTE(v22) = v22 & 0xFE;
    *(_DWORD *)(v21 + MEMORY[0x503300]) = v22;
    *(_DWORD *)(v21 + MEMORY[0x503300]) |= 2u;
    *(_DWORD *)(v21 + MEMORY[0x503300] + 16) = a5;
    if ( (*(_BYTE *)(a1 + 16) & 4) == 0 )
    {
      v23 = *(_DWORD *)(a1 + 96);
      v24 = (float *)(v23 + 12 * *(_DWORD *)(v21 + MEMORY[0x503300] + 12));
      v37[0] = *v24;
      v37[1] = v24[1];
      v37[2] = v24[2];
      v25 = (float *)(v23 + 12 * *(_DWORD *)(v21 + MEMORY[0x503300] + 16));
      v34 = *v25;
      v35 = v25[1];
      v36 = v25[2];
      cross_vectors(v38, v37, &v34);
      vector_magnitude(v38);
      if ( v14 <= 0.050000001 || dot_vector(v38, (float *)(v21 + MEMORY[0x503300] + 20)) > 0.0020000001 )
      {
        if ( v29 < MEMORY[0x503318] - 1 )
        {
          v26 = 36 * v29;
          do
          {
            ++v20;
            v27 = (const void *)(v26 + MEMORY[0x503300] + 36);
            v28 = (void *)(v26 + MEMORY[0x503300]);
            v26 += 36;
            qmemcpy(v28, v27, 0x24u);
          }
          while ( v20 < MEMORY[0x503318] - 1 );
        }
        --MEMORY[0x503318];
      }
    }
  }
}

