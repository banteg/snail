/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_x_mesh @ 0x405640 */
/* selector: load_x_mesh */

int __stdcall sub_405640(const char *a1, int *a2, char a3)
{
  char *v3; // esi
  char *v4; // eax
  char *v5; // edi
  char *v7; // eax
  char *v8; // eax
  char *v9; // eax
  int v10; // ebx
  int v11; // esi
  char *v12; // eax
  float *v13; // eax
  int v14; // ebp
  float *v15; // ebx
  int v16; // ebx
  int v17; // esi
  int v18; // ebx
  int v19; // eax
  int v20; // ebx
  __int16 v21; // cx
  int *v22; // eax
  int v23; // edx
  char *v24; // eax
  int v25; // esi
  _BYTE *v26; // eax
  char *v27; // esi
  int v28; // ebp
  int *v29; // ebx
  char *v30; // eax
  char *v31; // eax
  char i; // cl
  _BYTE *v33; // eax
  int *v34; // eax
  int v35; // ecx
  int v36; // ecx
  char *v37; // ebx
  int v38; // esi
  __int16 v39; // ax
  char *v40; // [esp+10h] [ebp-234h] BYREF
  int v41; // [esp+14h] [ebp-230h]
  char *v42; // [esp+18h] [ebp-22Ch] BYREF
  int v43; // [esp+1Ch] [ebp-228h]
  char *v44; // [esp+20h] [ebp-224h] BYREF
  _BYTE *v45; // [esp+24h] [ebp-220h]
  char *v46; // [esp+28h] [ebp-21Ch] BYREF
  char *v47; // [esp+2Ch] [ebp-218h] BYREF
  int v48; // [esp+30h] [ebp-214h]
  char *v49; // [esp+34h] [ebp-210h]
  int v50; // [esp+38h] [ebp-20Ch]
  _BYTE *v51; // [esp+3Ch] [ebp-208h]
  int v52; // [esp+40h] [ebp-204h] BYREF
  char Buffer[256]; // [esp+44h] [ebp-200h] BYREF
  _BYTE v54[2]; // [esp+144h] [ebp-100h] BYREF
  char v55; // [esp+146h] [ebp-FEh] BYREF

  v3 = (char *)get_archive_data_base();
  if ( !is_archive_index_loaded() || a1[strlen(a1) - 1] == 50 )
    sprintf(Buffer, "X/%s", a1);
  else
    sprintf(Buffer, "X/%s2", a1);
  load_file_bytes_from_archive_or_fs(Buffer, v3, (#83 *)&v52);
  v3[v52 - 2] = 0;
  v4 = find_case_insensitive_substring(aFrame, v3);
  v5 = v4;
  v49 = v4;
  if ( !v4 )
    return report_errorf("No 'Frame ' Data in %s", Buffer);
  v7 = find_case_insensitive_substring(aMesh, v4);
  v47 = v7;
  if ( !v7 )
  {
    report_errorf("No 'VertexDuplicationIndices 'Data in %s", Buffer);
    v7 = nullptr;
  }
  v47 = find_case_insensitive_substring(asc_4A1568, v7);
  v8 = find_case_insensitive_substring(aMesh, v5);
  v40 = v8;
  if ( !v8 )
  {
    report_errorf("No 'Mesh 'Data in %s", Buffer);
    v8 = nullptr;
  }
  v40 = find_case_insensitive_substring(asc_4A1568, v8);
  v9 = find_case_insensitive_substring(aMeshmaterialli, v5);
  v46 = v9;
  if ( !v9 )
  {
    report_errorf("No 'MeshMaterialList 'Data in %s", Buffer);
    v9 = nullptr;
  }
  v46 = find_case_insensitive_substring(asc_4A1568, v9);
  sub_44E710(&v46);
  LOWORD(v10) = sub_44E710(&v46);
  v41 = sub_44E710(&v47);
  v11 = (__int16)v41;
  if ( v11 != sub_44E710(&v40) )
    report_errorf("Mesh vertices count does not match vertext duplicate vertices count in %s", Buffer);
  sub_44E710(&v47);
  v12 = find_case_insensitive_substring(aMeshtexturecoo, v5);
  v44 = v12;
  if ( !v12 )
  {
    report_errorf("No 'Mesh 'Data in %s", Buffer);
    v12 = v44;
  }
  v44 = find_case_insensitive_substring(asc_4A1568, v12);
  if ( v11 != sub_44E710(&v44) )
    report_errorf("Mesh texture coords number does not match mesh vertext count in %s", Buffer);
  v10 = (__int16)v10;
  v48 = (__int16)v10;
  request_object_facequads(a2, (__int16)v10);
  request_object_vertices(a2, v11);
  v51 = allocate_tracked_memory(4 * v11, (int)aMeshVertexRema);
  v13 = (float *)allocate_tracked_memory(8 * v11, (int)aMeshTextureCoo_0);
  v14 = (int)v13;
  if ( v11 > 0 )
  {
    v15 = v13;
    v43 = v11;
    do
    {
      *v15 = parse_next_float32(&v44);
      v15[1] = parse_next_float32(&v44);
      v15 += 2;
      --v43;
    }
    while ( v43 );
    v10 = v48;
  }
  if ( (__int16)v41 > 0 )
  {
    v16 = 0;
    do
    {
      *(float *)(v16 + a2[14]) = parse_next_float32(&v40);
      *(float *)(v16 + a2[14] + 4) = parse_next_float32(&v40);
      *(float *)(v16 + a2[14] + 8) = parse_next_float32(&v40);
      v16 += 12;
      --v11;
    }
    while ( v11 );
    v10 = v48;
  }
  if ( v10 != sub_44E710(&v40) )
    report_errorf("Mesh face count does not match material face count in %s", Buffer);
  if ( v10 > 0 )
  {
    v17 = 0;
    v41 = v10;
    do
    {
      *(_WORD *)(v17 + a2[23]) = 0;
      v18 = sub_44E710(&v40);
      v50 = sub_44E710(&v40);
      v43 = sub_44E710(&v40);
      v19 = sub_44E710(&v40);
      v45 = (_BYTE *)v19;
      if ( v18 == 4 )
      {
        v20 = sub_44E710(&v40);
        v19 = (int)v45;
      }
      else
      {
        v20 = 0;
        *(_BYTE *)(v17 + a2[23]) |= 0x80u;
      }
      *(_DWORD *)(v17 + a2[23] + 32) = *(_DWORD *)(v14 + 8 * v50);
      *(_DWORD *)(v17 + a2[23] + 36) = *(_DWORD *)(v14 + 8 * v50 + 4);
      *(_DWORD *)(v17 + a2[23] + 24) = *(_DWORD *)(v14 + 8 * v43);
      *(_DWORD *)(v17 + a2[23] + 28) = *(_DWORD *)(v14 + 8 * v43 + 4);
      *(_DWORD *)(v17 + a2[23] + 16) = *(_DWORD *)(v14 + 8 * v19);
      *(_DWORD *)(v17 + a2[23] + 20) = *(_DWORD *)(v14 + 8 * v19 + 4);
      *(_DWORD *)(v17 + a2[23] + 40) = *(_DWORD *)(v14 + 8 * v20);
      *(_DWORD *)(v17 + a2[23] + 44) = *(_DWORD *)(v14 + 8 * v20 + 4);
      v17 += 48;
      *(_DWORD *)(v17 + a2[23] - 36) = get_or_create_texture_ref(&dword_4B7790, aXSnailTurboTga, 0, 0);
      v21 = v50;
      v22 = *(int **)(v17 + a2[23] - 36);
      v23 = *v22;
      BYTE1(v23) = BYTE1(*v22) | 0x10;
      *v22 = v23;
      *(_WORD *)(v17 + a2[23] - 42) = v21;
      *(_WORD *)(v17 + a2[23] - 44) = v43;
      *(_WORD *)(v17 + a2[23] - 46) = (_WORD)v45;
      *(_WORD *)(v17 + a2[23] - 40) = v20;
      --v41;
    }
    while ( v41 );
    v10 = v48;
  }
  a2[4] |= 0x100000u;
  free_tracked_memory(v14);
  free_tracked_memory((int)v51);
  v24 = find_case_insensitive_substring(aMeshmaterialli_0, v49);
  v42 = v24;
  if ( !v24 )
    return report_errorf("No MeshMaterialList { in %s", Buffer);
  v42 = find_case_insensitive_substring(asc_4A1568, v24);
  v25 = sub_44E710(&v42);
  v41 = v25;
  v49 = (char *)sub_44E710(&v42);
  if ( v49 != (char *)v10 )
    return report_errorf("No MeshMaterialList face number is not equal to Mesh face number in %s", Buffer);
  v26 = allocate_tracked_memory(4 * v25, (int)aDirectXMateria);
  v27 = v42;
  v28 = 0;
  v45 = v26;
  if ( v41 > 0 )
  {
    v29 = (int *)v26;
    do
    {
      v30 = find_case_insensitive_substring(aTexturefilenam, v27);
      if ( v30 )
      {
        v27 = find_case_insensitive_substring(asc_4A1314, v30) + 1;
        qmemcpy(v54, "X/", sizeof(v54));
        v31 = &v55;
        for ( i = *v27; i != 46; ++v27 )
        {
          *v31 = i;
          i = v27[1];
          ++v31;
        }
        *v31 = 46;
        v33 = v31 + 1;
        *v33++ = 116;
        *v33++ = 103;
        *v33 = 97;
        v33[1] = 0;
        v34 = (int *)get_or_create_texture_ref(&dword_4B7790, v54, 0, 0);
        *v29 = (int)v34;
        v35 = *v34;
        BYTE1(v35) = BYTE1(*v34) | 0x10;
        *v34 = v35;
        if ( (a3 & 2) != 0 )
        {
          v36 = *(_DWORD *)*v29;
          BYTE1(v36) |= 0x80u;
          *(_DWORD *)*v29 = v36;
        }
      }
      else
      {
        if ( (a3 & 2) == 0 )
          report_warningf("No TextureFilename for Material %i in %s", v28, Buffer);
        *v29 = get_or_create_texture_ref(&dword_4B7790, aSpritesDebugTg_0, 0, 0);
        v27 = v42;
      }
      ++v28;
      ++v29;
    }
    while ( v28 < v41 );
  }
  v37 = v49;
  if ( (int)v49 > 0 )
  {
    v38 = 0;
    do
    {
      v39 = sub_44E710(&v42);
      v38 += 48;
      --v37;
      *(_DWORD *)(v38 + a2[23] - 36) = *(_DWORD *)&v45[4 * v39];
    }
    while ( v37 );
  }
  return free_tracked_memory((int)v45);
}

