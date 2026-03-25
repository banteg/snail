/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 */
/* selector: load_file_bytes_fixed_size_from_archive_or_fs */

// Loads exactly the caller-supplied byte count from a named archive entry or filesystem path, reusing the caller buffer when provided and otherwise allocating a tracked buffer before applying the archive XOR decode.
_BYTE *__cdecl load_file_bytes_fixed_size_from_archive_or_fs(char *FileName, _BYTE *Buffer, int ElementCount)
{
  int v3; // ebp
  char **v4; // edi
  char *v5; // edx
  const char *v6; // ebx
  char *v7; // esi
  char i; // cl
  char v9; // al
  _BYTE *tracked_memory; // edi
  int v12; // eax
  int v13; // eax
  #91 *v14; // eax
  FILE *v15; // esi
  _BYTE *v16; // edi
  char DstBuf[512]; // [esp+14h] [ebp-200h] BYREF

  update_loading_screen((int *)&flt_4DFAFC[36325]);
  if ( LODWORD(flt_4DFAFC[95039]) && (v3 = 0, (int)*(_DWORD *)LODWORD(flt_4DFAFC[95039]) > 0) )
  {
    v4 = (char **)(LODWORD(flt_4DFAFC[95039]) + 4);
    while ( 1 )
    {
      v5 = *v4;
      v6 = FileName;
      v7 = FileName;
      for ( i = **v4; i; ++v5 )
      {
        v9 = *v7;
        if ( !*v7 )
          break;
        if ( v9 >= 97 && v9 <= 122 )
          v9 -= 32;
        if ( i != v9 )
          break;
        i = v5[1];
        ++v7;
      }
      if ( !*v5 && !*v7 )
        break;
      ++v3;
      v4 += 3;
      if ( v3 >= *(_DWORD *)LODWORD(flt_4DFAFC[95039]) )
        goto LABEL_22;
    }
    tracked_memory = Buffer;
    if ( Buffer == (_BYTE *)-1 )
    {
      return *(_BYTE **)(LODWORD(flt_4DFAFC[95039]) + 12 * v3 + 8);
    }
    else
    {
      if ( Buffer )
      {
        v13 = ftell((FILE *)LODWORD(flt_4DFAFC[95037]));
        fseek((FILE *)LODWORD(flt_4DFAFC[95037]), *(_DWORD *)(12 * v3 + LODWORD(flt_4DFAFC[95039]) + 8) - v13, 1);
        fread(Buffer, 1, ElementCount, (FILE *)LODWORD(flt_4DFAFC[95037]));
        xor_archive_bytes_in_place(*(_DWORD *)(12 * v3 + LODWORD(flt_4DFAFC[95039]) + 8), (int)Buffer, ElementCount);
      }
      else
      {
        tracked_memory = allocate_tracked_memory(ElementCount, (int)FileName);
        v12 = ftell((FILE *)LODWORD(flt_4DFAFC[95037]));
        fseek((FILE *)LODWORD(flt_4DFAFC[95037]), *(_DWORD *)(12 * v3 + LODWORD(flt_4DFAFC[95039]) + 8) - v12, 1);
        fread(tracked_memory, 1, ElementCount, (FILE *)LODWORD(flt_4DFAFC[95037]));
        xor_archive_bytes_in_place(
          *(_DWORD *)(12 * v3 + LODWORD(flt_4DFAFC[95039]) + 8),
          (int)tracked_memory,
          ElementCount);
      }
      return tracked_memory;
    }
  }
  else
  {
    v6 = FileName;
LABEL_22:
    v14 = fopen(v6, Mode);
    v15 = v14;
    if ( v14 )
    {
      get_stream_length_preserve_position(v14);
      v16 = Buffer;
      if ( !Buffer || Buffer == (_BYTE *)-1 )
        v16 = allocate_tracked_memory(ElementCount, (int)FileName);
      fread(v16, 1, ElementCount, v15);
      fclose(v15);
      return v16;
    }
    else
    {
      _getcwd(DstBuf, 512);
      report_messagef("WARNING:Cannot find file : %s (from %s)\n", v6, DstBuf);
      return nullptr;
    }
  }
}

