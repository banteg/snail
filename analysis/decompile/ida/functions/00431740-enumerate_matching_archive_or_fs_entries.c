/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: enumerate_matching_archive_or_fs_entries @ 0x431740 */
/* selector: enumerate_matching_archive_or_fs_entries */

// Windows RShellReadDirectory(char*, char*, int*, char (*)[128]): enumerates archive-backed or filesystem-backed filenames under the requested prefix, filters them against the caller wildcard pattern, copies each match into caller-owned 128-byte name records, and returns the match count through the out parameter. The archive path walks 12-byte ArchiveEntry records and reloads the shared ArchiveIndex owner at each loop tail.
void __cdecl enumerate_matching_archive_or_fs_entries(
        char *directory,
        char *pattern,
        int *out_count,
        EnumeratedEntryName *names)
{
  ArchiveIndex *v4; // eax
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
  FileSearchData v18; // [esp+14h] [ebp-318h] BYREF
  char Path[512]; // [esp+12Ch] [ebp-200h] BYREF

  v4 = g_archive_index_records;
  g_enumerated_entry_count = 0;
  if ( g_archive_index_records )
  {
    v17 = 0;
    if ( g_archive_index_records->count > 0 )
    {
      v16 = 0;
      do
      {
        v5 = directory;
        v6 = v4->entries[v16].path;
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
              v12 = pattern[v11];
              if ( !v12 )
                break;
              v15 = ascii_upper_if_lowercase(v9[v10]);
              if ( v15 != ascii_upper_if_lowercase(v12) && pattern[v11] != 42 )
                break;
              if ( pattern[v11] == 42 && v9[v10] == pattern[v11 + 1] )
                ++v11;
              ++v10;
              if ( pattern[v11] != 42 )
                ++v11;
            }
            while ( v9[v10] );
          }
          if ( !v9[v10] )
          {
            rstrcpy_checked_ascii(&(*names)[128 * g_enumerated_entry_count], v9);
            ++g_enumerated_entry_count;
          }
        }
        v4 = g_archive_index_records;
        v13 = ++v17 < g_archive_index_records->count;
        ++v16;
      }
      while ( v13 );
    }
    *out_count = g_enumerated_entry_count;
  }
  else
  {
    getcwd(Path, 512);
    if ( set_current_directory_with_drive_fallback(directory) == 1 )
    {
      *out_count = g_enumerated_entry_count;
    }
    else
    {
      v14 = findfirst(pattern, &v18);
      if ( v14 != -1 )
      {
        rstrcpy_checked_ascii(&(*names)[128 * g_enumerated_entry_count], v18.name);
        ++g_enumerated_entry_count;
        for ( ; findnext(v14, &v18) != -1; ++g_enumerated_entry_count )
          rstrcpy_checked_ascii(&(*names)[128 * g_enumerated_entry_count], v18.name);
      }
      *out_count = g_enumerated_entry_count;
      chdir(Path);
    }
  }
}
