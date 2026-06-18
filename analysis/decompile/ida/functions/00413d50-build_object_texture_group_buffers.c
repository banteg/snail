/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: build_object_texture_group_buffers @ 0x413d50 */
/* selector: build_object_texture_group_buffers */

// Allocates one built object's texture-group tables, expands each grouped face run into triangle indices, and builds the matching Direct3D vertex and index buffers for grouped rendering.
int *__usercall sub_413D50@<eax>(int a1@<esi>, _DWORD *a2, int a3)
{
  int *result; // eax
  int v5; // edi
  _BYTE *v6; // eax
  _BYTE *v7; // eax
  int v8; // ecx
  int v9; // ebp
  int i; // esi
  int v11; // eax
  int v12; // eax
  int v13; // ecx
  int v14; // edx
  int v15; // eax
  int v16; // edi
  char *v17; // esi
  _WORD *v18; // ebp
  int v19; // eax
  int v20; // ecx
  int *v21; // eax
  int v22; // edx
  int v23; // edx
  int v24; // eax
  int v25; // ecx
  _DWORD *v26; // esi
  int v27; // esi
  _DWORD *v28; // edi
  int v29; // ebp
  int v30; // [esp-1Ch] [ebp-50h]
  int v31; // [esp-14h] [ebp-48h]
  char *v33; // [esp+Ch] [ebp-28h]
  char *v34; // [esp+10h] [ebp-24h]
  _WORD *v35; // [esp+14h] [ebp-20h]
  int v36; // [esp+18h] [ebp-1Ch]
  _WORD *v37; // [esp+1Ch] [ebp-18h]
  int v38; // [esp+20h] [ebp-14h]
  int v39; // [esp+24h] [ebp-10h] BYREF
  int v40; // [esp+28h] [ebp-Ch]
  char *v41; // [esp+2Ch] [ebp-8h]
  char *v42; // [esp+30h] [ebp-4h] BYREF
  int v43; // [esp+38h] [ebp+4h]

  result = (int *)a2[11];
  v5 = 0;
  if ( result )
  {
    a2[4] |= 0x80000u;
    v6 = allocate_tracked_memory(4 * a2[25], (int)aDxTexturegroup);
    v31 = 4 * a2[25];
    a2[51] = v6;
    v7 = allocate_tracked_memory(v31, (int)aDxTexturegroup_0);
    v30 = 4 * a2[25];
    a2[52] = v7;
    a2[53] = allocate_tracked_memory(v30, (int)aDxTexturegroup_1);
    unk_5031C4 = get_archive_data_base();
    v41 = (char *)get_archive_data_end();
    unk_5031BC = 0;
    v8 = 0;
    v9 = 0;
    v38 = 0;
    v43 = 0;
    if ( (a2[4] & 4) != 0 )
    {
      for ( i = 0; i < a2[11]; ++i )
      {
        v11 = a2[21];
        v40 = 0;
        if ( v11 > 0 )
        {
          do
          {
            v12 = v5 + a2[23];
            if ( *(unsigned __int16 *)(v12 + 2) == i )
            {
              get_or_append_object_texture_group_vertex(a2, i, *(float *)(v12 + 16), *(float *)(v12 + 20));
            }
            else if ( *(unsigned __int16 *)(v12 + 4) == i )
            {
              get_or_append_object_texture_group_vertex(a2, i, *(float *)(v12 + 24), *(float *)(v12 + 28));
            }
            else if ( *(unsigned __int16 *)(v12 + 6) == i )
            {
              get_or_append_object_texture_group_vertex(a2, i, *(float *)(v12 + 32), *(float *)(v12 + 36));
            }
            else if ( *(char *)v12 >= 0 && *(unsigned __int16 *)(v12 + 8) == i )
            {
              get_or_append_object_texture_group_vertex(a2, i, *(float *)(v12 + 40), *(float *)(v12 + 44));
            }
            v13 = a2[21];
            v5 += 48;
            ++v40;
          }
          while ( v40 < v13 );
          v8 = 0;
          v5 = 0;
        }
      }
    }
    v14 = a2[25];
    v15 = 0;
    v40 = 0;
    if ( v14 > 0 )
    {
      while ( 1 )
      {
        v36 = 0;
        v16 = 48 * v8;
        *(_DWORD *)(a2[52] + 4 * v15) = *(_DWORD *)(48 * v8 + a2[23] + 12);
        *(_DWORD *)(a2[51] + 4 * v15) = v9;
        if ( v8 < *(_DWORD *)(a2[27] + 4 * v15) )
        {
          v17 = &v41[2 * v9];
          v37 = v17 + 10;
          v18 = v17 + 4;
          v35 = v17 + 8;
          v34 = &v41[2 * v43 + 6];
          v33 = &v41[2 * v43 + 2];
          do
          {
            *(_WORD *)v17 = get_or_append_object_texture_group_vertex(
                              a2,
                              *(unsigned __int16 *)(v16 + a2[23] + 2),
                              *(float *)(v16 + a2[23] + 16),
                              *(float *)(v16 + a2[23] + 20));
            *(_WORD *)v33 = get_or_append_object_texture_group_vertex(
                              a2,
                              *(unsigned __int16 *)(v16 + a2[23] + 4),
                              *(float *)(v16 + a2[23] + 24),
                              *(float *)(v16 + a2[23] + 28));
            *v18 = get_or_append_object_texture_group_vertex(
                     a2,
                     *(unsigned __int16 *)(v16 + a2[23] + 6),
                     *(float *)(v16 + a2[23] + 32),
                     *(float *)(v16 + a2[23] + 36));
            if ( *(char *)(v16 + a2[23]) < 0 )
            {
              v43 += 3;
              v17 += 6;
              v33 += 6;
              v18 += 3;
              v34 += 6;
              v35 += 3;
              v37 += 3;
              v19 = v36 + 1;
            }
            else
            {
              *(_WORD *)v34 = *(_WORD *)v17;
              *v35 = *v18;
              *v37 = get_or_append_object_texture_group_vertex(
                       a2,
                       *(unsigned __int16 *)(v16 + a2[23] + 8),
                       *(float *)(v16 + a2[23] + 40),
                       *(float *)(v16 + a2[23] + 44));
              v43 += 6;
              v17 += 12;
              v33 += 12;
              v18 += 6;
              v34 += 12;
              v35 += 6;
              v37 += 6;
              v19 = v36 + 2;
            }
            v36 = v19;
            v16 += 48;
            ++v38;
          }
          while ( v38 < *(_DWORD *)(a2[27] + 4 * v40) );
          v9 = v43;
          v15 = v40;
        }
        *(_DWORD *)(a2[53] + 4 * v15) = v36;
        v20 = a2[25];
        v40 = ++v15;
        if ( v15 >= v20 )
          break;
        v8 = v38;
      }
    }
    a2[49] = unk_5031BC;
    a2[48] = create_object_vertex_buffer_resource(unk_4F7458, unk_5031BC, 322);
    v21 = create_object_index_buffer_resource(unk_5000FC, v9);
    v22 = a2[48];
    a2[50] = v21;
    (*(void (__stdcall **)(_DWORD, _DWORD, int, int *, _DWORD, int))(**(_DWORD **)(v22 + 8) + 44))(
      *(_DWORD *)(v22 + 8),
      0,
      24 * unk_5031BC,
      &v39,
      0,
      a1);
    v23 = 0;
    if ( unk_5031BC > 0 )
    {
      v24 = 0;
      v25 = 0;
      do
      {
        *(_DWORD *)(v24 + v40 + 12) = *(_DWORD *)(v25 + unk_5031C4 + 12);
        v26 = (_DWORD *)(v25 + unk_5031C4 + 16);
        *(_DWORD *)(v24 + v40 + 16) = *v26;
        *(_DWORD *)(v24 + v40 + 20) = v26[1];
        v27 = v25 + unk_5031C4;
        v28 = (_DWORD *)(v24 + v40);
        ++v23;
        v29 = *(_DWORD *)(v25 + unk_5031C4);
        v25 += 28;
        *v28 = v29;
        v24 += 24;
        v28[1] = *(_DWORD *)(v27 + 4);
        v28[2] = *(_DWORD *)(v27 + 8);
      }
      while ( v23 < unk_5031BC );
      v9 = a3;
    }
    (*(void (__cdecl **)(_DWORD))(**(_DWORD **)(a2[48] + 8) + 48))(*(_DWORD *)(a2[48] + 8));
    (*(void (__stdcall **)(_DWORD, _DWORD, int, char **, _DWORD))(**(_DWORD **)a2[50] + 44))(
      *(_DWORD *)a2[50],
      0,
      2 * v9,
      &v42,
      0);
    qmemcpy(v42, v41, 2 * v9);
    (*(void (__stdcall **)(_DWORD))(**(_DWORD **)a2[50] + 48))(*(_DWORD *)a2[50]);
    result = (int *)a2[4];
    if ( (BYTE1(result) & 0x40) != 0 )
    {
      result = create_object_index_buffer_resource(unk_5000FC, v9);
      a2[54] = result;
    }
  }
  else
  {
    a2[51] = 0;
    a2[52] = 0;
    a2[53] = 0;
    a2[48] = 0;
    a2[50] = 0;
  }
  return result;
}

