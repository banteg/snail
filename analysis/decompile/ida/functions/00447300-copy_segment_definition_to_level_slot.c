/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: copy_segment_definition_to_level_slot @ 0x447300 */
/* selector: copy_segment_definition_to_level_slot */

// Finds a segment catalog entry by its enumerated filename, transposes its column-major eight-lane glyph grid into a Windows SubSegment, and copies the authored position/velocity vectors, path template, and ring-speed fields. The symbol-preserving iOS counterpart is the void member `cRSubTracks::ImportSegment(char*, cRSubSegment*)`; Windows staticizes the catalog lookup and owns the 0x4220-byte payload inline.
_DWORD *__stdcall copy_segment_definition_to_level_slot(char *ArgList, _DWORD *a2)
{
  _DWORD *v2; // edi
  int v3; // esi
  char *v4; // ebp
  _DWORD *result; // eax
  _DWORD *v6; // ebp
  _DWORD *v7; // edx
  _DWORD *v8; // edi
  char *v9; // ecx
  int v10; // eax
  char *v11; // esi
  char v12; // bl
  int v13; // esi
  _DWORD *v14; // ecx
  _DWORD *v15; // edi
  _DWORD *v16; // ebx
  int ArgLista; // [esp+14h] [ebp+4h]

  v2 = (char *)MEMORY[0x4DF904] + 17259236;
  v3 = 0;
  if ( *((int *)MEMORY[0x4DF904] + 4314809) > 0 )
  {
    v4 = (char *)MEMORY[0x4DF904] + 17259304;
    do
    {
      if ( strings_equal_case_insensitive_path(ArgList, v4) == 1 )
        break;
      ++v3;
      v4 += 16520;
    }
    while ( v3 < *v2 );
  }
  if ( v3 == *v2 )
    return (_DWORD *)report_errorf("Cannot find segment %s for %s", ArgList, unk_74EC74);
  v6 = a2;
  ArgLista = 8;
  v7 = &v2[4130 * v3];
  v8 = a2 + 5;
  v9 = (char *)(v7 + 35);
  do
  {
    v10 = 0;
    if ( (int)v7[34] > 0 )
    {
      v11 = v9;
      do
      {
        v12 = *v11;
        v11 += 8;
        *((_BYTE *)v8 + v10++) = v12;
      }
      while ( v10 < v7[34] );
    }
    ++v9;
    v8 += 64;
    --ArgLista;
  }
  while ( ArgLista );
  v13 = 0;
  a2[1] = v7[34];
  a2[4] = v7 + 17;
  a2[4101] = 0;
  a2[3] = v7[33];
  result = (_DWORD *)v7[34];
  if ( (int)result > 0 )
  {
    v14 = a2 + 522;
    result = v7 + 552;
    do
    {
      *(v14 - 5) = *(result - 5);
      *v14 = *result;
      ++v13;
      v14[1] = result[1];
      v14[2] = result[2];
      v14[3] = result[3];
      v14[4] = result[4];
      v14[5] = result[5];
      v14[6] = result[6];
      *(v14 - 4) = *(result - 4);
      v15 = result - 3;
      v16 = v14 - 3;
      result += 14;
      v14 += 14;
      *v16 = *v15;
      v16[1] = v15[1];
      v16[2] = v15[2];
      *(v14 - 7) = *(result - 7);
      *(v14 - 6) = *(result - 6);
    }
    while ( v13 < v7[34] );
    v6 = a2;
  }
  *((_BYTE *)v6 + 16408) = 0;
  v6[4230] = 0;
  v6[4231] = -1;
  return result;
}
