/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enumerate_matching_archive_or_fs_entries @ 0x431740 */
/* selector: enumerate_matching_archive_or_fs_entries */

// Enumerates archive-backed or filesystem-backed filenames under the requested prefix, filters them against the caller wildcard pattern, copies each match into the fixed output table, and returns the match count through the out parameter.
int __cdecl enumerate_matching_archive_or_fs_entries(char *a1, int lpFileName, float *a3, int a4)
{
  int result; // eax
  char *v5; // esi
  char *v6; // ecx
  char i; // dl
  char v8; // al
  char *v9; // ebp
  int v10; // edi
  int v11; // esi
  char v12; // bl
  bool v13; // cc
  int v14; // esi
  char v15; // [esp+Bh] [ebp-321h]
  int v16; // [esp+Ch] [ebp-320h]
  int v17; // [esp+10h] [ebp-31Ch]
  int v18[5]; // [esp+14h] [ebp-318h] BYREF
  char ArgList[260]; // [esp+28h] [ebp-304h] BYREF
  char Path[512]; // [esp+12Ch] [ebp-200h] BYREF

  result = LODWORD(flt_4DFAFC[95039]);
  flt_4DFAFC[36361] = 0.0;
  if ( LODWORD(flt_4DFAFC[95039]) )
  {
    v17 = 0;
    if ( (int)*(_DWORD *)LODWORD(flt_4DFAFC[95039]) > 0 )
    {
      v16 = 0;
      do
      {
        v5 = a1;
        v6 = *(char **)(v16 + result + 4);
        for ( i = *v6; i; ++v6 )
        {
          v8 = *v5;
          if ( !*v5 )
            break;
          if ( v8 >= 97 && v8 <= 122 )
            v8 -= 32;
          if ( i != v8 )
            break;
          i = v6[1];
          ++v5;
        }
        if ( *v6 == 47 && !*v5 )
        {
          v9 = v6 + 1;
          v10 = 0;
          v11 = 0;
          if ( v6[1] )
          {
            do
            {
              v12 = *(_BYTE *)(v11 + lpFileName);
              if ( !v12 )
                break;
              v15 = ascii_upper_if_lowercase(v9[v10]);
              if ( v15 != ascii_upper_if_lowercase(v12) && *(_BYTE *)(v11 + lpFileName) != 42 )
                break;
              if ( *(_BYTE *)(v11 + lpFileName) == 42 && v9[v10] == *(_BYTE *)(v11 + lpFileName + 1) )
                ++v11;
              ++v10;
              if ( *(_BYTE *)(v11 + lpFileName) != 42 )
                ++v11;
            }
            while ( v9[v10] );
          }
          if ( !v9[v10] )
          {
            rstrcpy_checked_ascii((char *)(a4 + (LODWORD(flt_4DFAFC[36361]) << 7)), v9);
            ++LODWORD(flt_4DFAFC[36361]);
          }
        }
        result = LODWORD(flt_4DFAFC[95039]);
        v13 = ++v17 < *(_DWORD *)LODWORD(flt_4DFAFC[95039]);
        v16 += 12;
      }
      while ( v13 );
    }
    *a3 = flt_4DFAFC[36361];
  }
  else
  {
    _getcwd(Path, 512);
    if ( set_current_directory_with_drive_fallback(a1) == 1 )
    {
      result = LODWORD(flt_4DFAFC[36361]);
      *a3 = flt_4DFAFC[36361];
    }
    else
    {
      v14 = _findfirst(lpFileName, v18);
      if ( v14 != -1 )
      {
        rstrcpy_checked_ascii((char *)(a4 + (LODWORD(flt_4DFAFC[36361]) << 7)), ArgList);
        ++LODWORD(flt_4DFAFC[36361]);
        for ( ; _findnext(v14, v18) != -1; ++LODWORD(flt_4DFAFC[36361]) )
          rstrcpy_checked_ascii((char *)(a4 + (LODWORD(flt_4DFAFC[36361]) << 7)), ArgList);
      }
      *a3 = flt_4DFAFC[36361];
      return _chdir(Path);
    }
  }
  return result;
}

