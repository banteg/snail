/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: get_or_append_object_texture_group_vertex @ 0x413bb0 */
/* selector: get_or_append_object_texture_group_vertex */

// Returns the existing grouped-render vertex matching one object vertex index plus UVs, or appends a new grouped vertex into the temporary texture-group build buffer when no match exists.
int __cdecl sub_413BB0(_DWORD *a1, int a2, float a3, float a4)
{
  float *v4; // edx
  int v5; // edx
  int v6; // ecx
  int v7; // esi
  float v9; // [esp+10h] [ebp-Ch]
  float v10; // [esp+14h] [ebp-8h]
  float v11; // [esp+18h] [ebp-4h]

  if ( a2 >= a1[11] )
    report_errorf(aVertexrefOutOf);
  v4 = (float *)(a1[14] + 12 * a2);
  v9 = *v4;
  v10 = v4[1];
  v11 = v4[2];
  v5 = 0;
  if ( MEMORY[0x5031BC] > 0 )
  {
    v6 = MEMORY[0x5031C4] + 4;
    do
    {
      if ( (a1[4] & 4) != 0 )
      {
        if ( *(_DWORD *)(v6 + 20) == a2 && *(float *)(v6 + 12) == a3 && 1.0 - a4 == *(float *)(v6 + 16) )
          return v5;
      }
      else if ( *(float *)(v6 - 4) == v9
             && *(float *)v6 == v10
             && *(float *)(v6 + 4) == v11
             && *(float *)(v6 + 12) == a3
             && 1.0 - a4 == *(float *)(v6 + 16) )
      {
        return v5;
      }
      ++v5;
      v6 += 28;
    }
    while ( v5 < MEMORY[0x5031BC] );
  }
  v7 = 28 * v5;
  *(float *)(v7 + MEMORY[0x5031C4]) = v9;
  *(float *)(v7 + MEMORY[0x5031C4] + 4) = v10;
  *(float *)(v7 + MEMORY[0x5031C4] + 8) = v11;
  *(float *)(v7 + MEMORY[0x5031C4] + 16) = a3;
  *(float *)(v7 + MEMORY[0x5031C4] + 20) = 1.0 - a4;
  if ( (a1[4] & 0x10000) != 0 )
    pack_color_rgba_u8((_BYTE *)(v7 + MEMORY[0x5031C4] + 12), (float *)(16 * a2 + a1[18]));
  else
    *(_DWORD *)(v7 + MEMORY[0x5031C4] + 12) = -1;
  *(_DWORD *)(v7 + MEMORY[0x5031C4] + 24) = a2;
  return MEMORY[0x5031BC]++;
}

