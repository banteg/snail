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
  ArchiveIndex *archive_index; // eax
  char *directory_cursor; // esi
  char *archive_path_cursor; // ecx
  char archive_path_char; // dl
  char directory_char; // al
  char *basename_cursor; // ebp
  int basename_index; // edi
  int pattern_index; // esi
  char pattern_char; // bl
  bool v13; // cc
  int filesystem_handle; // esi
  char folded_basename_char; // [esp+Bh] [ebp-321h]
  int archive_entry_offset; // [esp+Ch] [ebp-320h]
  int archive_entry_index; // [esp+10h] [ebp-31Ch]
  FileSearchData find_data; // [esp+14h] [ebp-318h] BYREF
  char cwd_buffer[512]; // [esp+12Ch] [ebp-200h] BYREF

  archive_index = g_archive_index_records;
  g_enumerated_entry_count = 0;
  if ( g_archive_index_records )
  {
    archive_entry_index = 0;
    if ( g_archive_index_records->count > 0 )
    {
      archive_entry_offset = 0;
      do
      {
        directory_cursor = directory;
        archive_path_cursor = archive_index->entries[archive_entry_offset].path;
        for ( archive_path_char = *archive_path_cursor; archive_path_char; ++archive_path_cursor )
        {
          directory_char = *directory_cursor;
          if ( !*directory_cursor )
            break;
          if ( directory_char >= 97 && directory_char <= 122 )
            directory_char -= 32;
          if ( archive_path_char != directory_char )
            break;
          archive_path_char = archive_path_cursor[1];
          ++directory_cursor;
        }
        if ( *archive_path_cursor == 47 && !*directory_cursor )
        {
          basename_cursor = archive_path_cursor + 1;
          basename_index = 0;
          pattern_index = 0;
          if ( archive_path_cursor[1] )
          {
            do
            {
              pattern_char = pattern[pattern_index];
              if ( !pattern_char )
                break;
              folded_basename_char = ascii_upper_if_lowercase(basename_cursor[basename_index]);
              if ( folded_basename_char != ascii_upper_if_lowercase(pattern_char) && pattern[pattern_index] != 42 )
                break;
              if ( pattern[pattern_index] == 42 && basename_cursor[basename_index] == pattern[pattern_index + 1] )
                ++pattern_index;
              ++basename_index;
              if ( pattern[pattern_index] != 42 )
                ++pattern_index;
            }
            while ( basename_cursor[basename_index] );
          }
          if ( !basename_cursor[basename_index] )
          {
            rstrcpy_checked_ascii(&(*names)[128 * g_enumerated_entry_count], basename_cursor);
            ++g_enumerated_entry_count;
          }
        }
        archive_index = g_archive_index_records;
        v13 = ++archive_entry_index < g_archive_index_records->count;
        ++archive_entry_offset;
      }
      while ( v13 );
    }
    *out_count = g_enumerated_entry_count;
  }
  else
  {
    getcwd(cwd_buffer, 512);
    if ( set_current_directory_with_drive_fallback(directory) == 1 )
    {
      *out_count = g_enumerated_entry_count;
    }
    else
    {
      filesystem_handle = findfirst(pattern, &find_data);
      if ( filesystem_handle != -1 )
      {
        rstrcpy_checked_ascii(&(*names)[128 * g_enumerated_entry_count], find_data.name);
        ++g_enumerated_entry_count;
        for ( ; findnext(filesystem_handle, &find_data) != -1; ++g_enumerated_entry_count )
          rstrcpy_checked_ascii(&(*names)[128 * g_enumerated_entry_count], find_data.name);
      }
      *out_count = g_enumerated_entry_count;
      chdir(cwd_buffer);
    }
  }
}
