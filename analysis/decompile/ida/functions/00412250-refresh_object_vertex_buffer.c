/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: refresh_object_vertex_buffer @ 0x412250 */
/* selector: refresh_object_vertex_buffer */

// Refreshes one built object's grouped vertex buffer from the current animated or distorted vertex source, preserving the authored UV lanes for the grouped draw path.
void __cdecl sub_412250(_DWORD *a1)
{
  int v1; // esi
  int v2; // ebx
  int v3; // edi
  int v4; // eax
  int v5; // edx
  int v6; // ecx
  _DWORD *v7; // edi
  _DWORD *v8; // ebx
  int v9; // ecx
  int v10; // edi
  int v11; // ebx
  _DWORD *v12; // edx
  _DWORD *v13; // eax
  int v14; // eax
  int v15; // edx
  int v16; // eax

  v1 = (int)a1;
  v2 = a1[4];
  if ( (v2 & 0x200000) != 0 )
  {
    v3 = a1[47];
    a1[14] = **(_DWORD **)(*(_DWORD *)(v3 + 8) + 4 * (__int64)((double)*(int *)(v3 + 4) * *(float *)(v3 + 12)));
    *(_DWORD *)(v1 + 96) = *(_DWORD *)(*(_DWORD *)(*(_DWORD *)(v3 + 8)
                                                 + 4 * (__int64)((double)*(int *)(v3 + 4) * *(float *)(v3 + 12)))
                                     + 4);
    if ( ((unsigned int)&unk_800000 & v2) != 0 )
      apply_distort_to_object((float *)(v1 + 128), v1);
    (*(void (__stdcall **)(_DWORD, _DWORD, int, _DWORD **, _DWORD))(**(_DWORD **)(*(_DWORD *)(v1 + 192) + 8) + 44))(
      *(_DWORD *)(*(_DWORD *)(v1 + 192) + 8),
      0,
      24 * *(_DWORD *)(v1 + 196),
      &a1,
      0);
    v4 = 0;
    if ( *(int *)(v1 + 196) > 0 )
    {
      v5 = 0;
      v6 = 0;
      do
      {
        v7 = (_DWORD *)(*(_DWORD *)(v1 + 56) + v6);
        v8 = &a1[v5];
        ++v4;
        v6 += 12;
        *v8 = *v7;
        v5 += 6;
        v8[1] = v7[1];
        v8[2] = v7[2];
      }
      while ( v4 < *(_DWORD *)(v1 + 196) );
    }
  }
  else
  {
    if ( (v2 & 4) == 0 )
      return;
    (*(void (__stdcall **)(_DWORD, _DWORD, int, _DWORD **, _DWORD))(**(_DWORD **)(a1[48] + 8) + 44))(
      *(_DWORD *)(a1[48] + 8),
      0,
      24 * a1[49],
      &a1,
      0);
    v9 = 0;
    if ( *(int *)(v1 + 196) > 0 )
    {
      v10 = 0;
      v11 = 0;
      do
      {
        v12 = (_DWORD *)(*(_DWORD *)(v1 + 56) + v11);
        v13 = &a1[v10];
        v11 += 12;
        v10 += 6;
        *v13 = *v12;
        v13[1] = v12[1];
        v13[2] = v12[2];
        v14 = v9 / 4;
        v15 = v9++ & 3;
        v16 = v15 + 6 * v14;
        a1[v10 - 2] = *(_DWORD *)(*(_DWORD *)(v1 + 92) + 8 * v16 + 16);
        a1[v10 - 1] = *(_DWORD *)(*(_DWORD *)(v1 + 92) + 8 * v16 + 20);
      }
      while ( v9 < *(_DWORD *)(v1 + 196) );
    }
  }
  (*(void (__stdcall **)(_DWORD))(**(_DWORD **)(*(_DWORD *)(v1 + 192) + 8) + 48))(*(_DWORD *)(*(_DWORD *)(v1 + 192) + 8));
}

