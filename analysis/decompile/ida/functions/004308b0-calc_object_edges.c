/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: calc_object_edges @ 0x4308b0 */
/* selector: calc_object_edges */

// Builds the unique edge list for one toon-enabled object from its face quads, optionally removes boundary edges for closed meshes, and stores the packed records later filtered by `render_object_toon`.
void __usercall sub_4308B0(int a1@<ecx>, double a2@<st0>)
{
  int v3; // esi
  int v4; // edi
  int v5; // ecx
  int v6; // edi
  int v7; // eax
  int v8; // edx
  int v9; // ebx
  int v10; // [esp+4h] [ebp-4h]
  int v11; // [esp+4h] [ebp-4h]

  if ( (*(_BYTE *)(a1 + 16) & 1) != 0 )
  {
    v3 = *(_DWORD *)(a1 + 92);
    v4 = get_archive_data_base();
    v5 = 0;
    MEMORY[0x503300] = v4;
    MEMORY[0x503318] = 0;
    v10 = 0;
    if ( *(int *)(a1 + 84) > 0 )
    {
      v6 = 0;
      do
      {
        add_object_edge(a1, a2, *(unsigned __int16 *)(v3 + 2), *(unsigned __int16 *)(v3 + 4), v6);
        add_object_edge(a1, a2, *(unsigned __int16 *)(v3 + 6), *(unsigned __int16 *)(v3 + 2), v6);
        add_object_edge(a1, a2, *(unsigned __int16 *)(v3 + 4), *(unsigned __int16 *)(v3 + 6), v6);
        if ( *(char *)v3 >= 0 )
        {
          add_object_edge(a1, a2, *(unsigned __int16 *)(v3 + 2), *(unsigned __int16 *)(v3 + 6), v6 + 1);
          add_object_edge(a1, a2, *(unsigned __int16 *)(v3 + 8), *(unsigned __int16 *)(v3 + 2), v6 + 1);
          add_object_edge(a1, a2, *(unsigned __int16 *)(v3 + 6), *(unsigned __int16 *)(v3 + 8), v6 + 1);
        }
        v3 += 48;
        v6 += 2;
        ++v10;
      }
      while ( v10 < *(_DWORD *)(a1 + 84) );
      v4 = MEMORY[0x503300];
      v5 = MEMORY[0x503318];
    }
    if ( (BYTE1(*(_DWORD *)(a1 + 16)) & 0x80u) != 0 )
    {
      v7 = 0;
      if ( v5 > 0 )
      {
        v8 = 0;
        v11 = 0;
        do
        {
          if ( (*(_BYTE *)(v8 + v4) & 1) != 0 )
          {
            v9 = v7;
            if ( v7 < v5 - 1 )
            {
              do
              {
                ++v9;
                qmemcpy((void *)(v8 + v4), (const void *)(v8 + v4 + 36), 0x24u);
                v5 = MEMORY[0x503318];
                v4 = MEMORY[0x503300];
                v8 += 36;
              }
              while ( v9 < MEMORY[0x503318] - 1 );
              v8 = v11;
            }
            --v5;
            --v7;
            MEMORY[0x503318] = v5;
            v8 -= 36;
          }
          ++v7;
          v8 += 36;
          v11 = v8;
        }
        while ( v7 < v5 );
      }
    }
    request_object_edges((_DWORD *)a1, v5);
    qmemcpy(*(void **)(a1 + 116), (const void *)MEMORY[0x503300], 36 * MEMORY[0x503318]);
  }
}

