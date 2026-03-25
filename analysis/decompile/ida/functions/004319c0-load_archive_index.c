/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_archive_index @ 0x4319c0 */
/* selector: load_archive_index */

// Decodes and parses the SnailMail.dat archive index into lookup records for archive-backed file loading.
char __cdecl load_archive_index(char *FileName)
{
  int v2; // edi
  int *v3; // esi
  float v4; // eax
  int v5; // edx
  int v6; // ecx
  int v7; // esi
  _BYTE Buffer[8]; // [esp+4h] [ebp-7Ch] BYREF
  int ElementCount[29]; // [esp+Ch] [ebp-74h]

  flt_4DFAFC[95039] = 0.0;
  if ( archive_or_file_exists(FileName, 0) )
  {
    load_file_bytes_fixed_size_from_archive_or_fs(FileName, Buffer, 124);
    xor_archive_bytes_in_place(0, (int)Buffer, 124);
    v2 = ElementCount[0];
    v3 = (int *)allocate_tracked_memory(ElementCount[0], (int)aDatFileHeader);
    load_file_bytes_fixed_size_from_archive_or_fs(FileName, v3, v2);
    xor_archive_bytes_in_place(0, (int)v3, v2);
    v4 = *(float *)&v3;
    LODWORD(flt_4DFAFC[95039]) = v3;
    v5 = 0;
    if ( *v3 > 0 )
    {
      v6 = 0;
      do
      {
        v7 = *(_DWORD *)(v6 + LODWORD(v4) + 4);
        v6 += 12;
        ++v5;
        *(_DWORD *)(v6 + LODWORD(v4) - 8) = LODWORD(v4) + v7;
        v4 = flt_4DFAFC[95039];
      }
      while ( v5 < *(_DWORD *)LODWORD(flt_4DFAFC[95039]) );
    }
    LODWORD(flt_4DFAFC[95037]) = fopen(FileName, Mode);
    return 1;
  }
  else
  {
    flt_4DFAFC[95039] = 0.0;
    return 1;
  }
}

