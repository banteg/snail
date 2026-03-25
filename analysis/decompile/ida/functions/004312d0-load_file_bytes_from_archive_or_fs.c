/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_from_archive_or_fs @ 0x4312d0 */
/* selector: load_file_bytes_from_archive_or_fs */

_BYTE *__cdecl load_file_bytes_from_archive_or_fs(char *FileName, _BYTE *Buffer, #83 *a3)
{
  int v3; // eax
  int v4; // edi
  char **v5; // ebx
  char *v6; // edx
  char *v7; // esi
  char v8; // cl
  char v9; // al
  #91 *v10; // eax
  FILE *v11; // esi
  _BYTE *v13; // ebx
  int v14; // esi
  int v15; // eax
  int v16; // edi
  int v17; // eax
  int v18; // esi
  int v19; // edi
  int v20; // eax
  _BYTE *v21; // ebx
  int v22; // edi
  char DstBuf[512]; // [esp+14h] [ebp-200h] BYREF

  update_loading_screen((int *)&flt_4DFAFC[36325]);
  if ( LODWORD(flt_4DFAFC[95039])
    && (v3 = *(_DWORD *)LODWORD(flt_4DFAFC[95039]), v4 = 0, (int)*(_DWORD *)LODWORD(flt_4DFAFC[95039]) > 0) )
  {
    v5 = (char **)(LODWORD(flt_4DFAFC[95039]) + 4);
    while ( 1 )
    {
      v6 = *v5;
      v7 = FileName;
      v8 = **v5;
      if ( v8 )
      {
        do
        {
          v9 = *v7;
          if ( !*v7 )
            break;
          if ( v9 >= 97 && v9 <= 122 )
            v9 -= 32;
          if ( v8 != v9 )
            break;
          v8 = v6[1];
          ++v7;
          ++v6;
        }
        while ( v8 );
        v3 = *(_DWORD *)LODWORD(flt_4DFAFC[95039]);
      }
      if ( !*v6 && !*v7 )
        break;
      ++v4;
      v5 += 3;
      if ( v4 >= v3 )
        goto LABEL_15;
    }
    if ( a3 )
      *(_DWORD *)a3 = *(_DWORD *)(LODWORD(flt_4DFAFC[95039]) + 4 * (3 * v4 + 3));
    v13 = Buffer;
    if ( Buffer == (_BYTE *)-1 )
    {
      return *(_BYTE **)(LODWORD(flt_4DFAFC[95039]) + 12 * v4 + 8);
    }
    else
    {
      if ( Buffer )
      {
        v17 = ftell((FILE *)LODWORD(flt_4DFAFC[95037]));
        v18 = 12 * v4;
        fseek((FILE *)LODWORD(flt_4DFAFC[95037]), *(_DWORD *)(12 * v4 + LODWORD(flt_4DFAFC[95039]) + 8) - v17, 1);
        v19 = 4 * (3 * v4 + 3);
        fread(Buffer, 1, *(_DWORD *)(v19 + LODWORD(flt_4DFAFC[95039])), (FILE *)LODWORD(flt_4DFAFC[95037]));
        xor_archive_bytes_in_place(
          *(_DWORD *)(v18 + LODWORD(flt_4DFAFC[95039]) + 8),
          (int)Buffer,
          *(_DWORD *)(v19 + LODWORD(flt_4DFAFC[95039])));
      }
      else
      {
        v14 = 4 * (3 * v4 + 3);
        v13 = allocate_tracked_memory(*(_DWORD *)(v14 + LODWORD(flt_4DFAFC[95039])), (int)FileName);
        v15 = ftell((FILE *)LODWORD(flt_4DFAFC[95037]));
        v16 = 12 * v4;
        fseek((FILE *)LODWORD(flt_4DFAFC[95037]), *(_DWORD *)(v16 + LODWORD(flt_4DFAFC[95039]) + 8) - v15, 1);
        fread(v13, 1, *(_DWORD *)(v14 + LODWORD(flt_4DFAFC[95039])), (FILE *)LODWORD(flt_4DFAFC[95037]));
        xor_archive_bytes_in_place(
          *(_DWORD *)(v16 + LODWORD(flt_4DFAFC[95039]) + 8),
          (int)v13,
          *(_DWORD *)(v14 + LODWORD(flt_4DFAFC[95039])));
      }
      return v13;
    }
  }
  else
  {
LABEL_15:
    v10 = fopen(FileName, Mode);
    v11 = v10;
    if ( v10 )
    {
      v20 = get_stream_length_preserve_position(v10);
      v21 = Buffer;
      v22 = v20;
      if ( !Buffer || Buffer == (_BYTE *)-1 )
        v21 = allocate_tracked_memory(v20, (int)FileName);
      fread(v21, 1, v22, v11);
      fclose(v11);
      if ( a3 )
        *(_DWORD *)a3 = v22;
      return v21;
    }
    else
    {
      _getcwd(DstBuf, 512);
      report_messagef("WARNING:Cannot find file : %s (from %s)\n", FileName, DstBuf);
      return nullptr;
    }
  }
}

