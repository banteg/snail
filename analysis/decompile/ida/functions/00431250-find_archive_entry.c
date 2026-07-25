/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_archive_entry @ 0x431250 */
/* selector: find_archive_entry */

ArchiveEntry *__cdecl find_archive_entry(char *path)
{
  int archive_entry_count; // eax
  int archive_entry_index; // ebx
  ArchiveEntry *archive_entry_cursor; // edi
  char *archive_path_cursor; // edx
  char *requested_path_cursor; // esi
  char archive_path_char; // cl
  char requested_path_char; // al

  if ( !g_archive_index_records )
    return nullptr;
  archive_entry_count = g_archive_index_records->count;
  archive_entry_index = 0;
  if ( g_archive_index_records->count <= 0 )
    return nullptr;
  for ( archive_entry_cursor = g_archive_index_records->entries; ; ++archive_entry_cursor )
  {
    archive_path_cursor = archive_entry_cursor->path;
    requested_path_cursor = path;
    archive_path_char = *archive_entry_cursor->path;
    if ( archive_path_char )
    {
      do
      {
        requested_path_char = *requested_path_cursor;
        if ( !*requested_path_cursor )
          break;
        if ( requested_path_char >= 97 && requested_path_char <= 122 )
          requested_path_char -= 32;
        if ( archive_path_char != requested_path_char )
          break;
        archive_path_char = archive_path_cursor[1];
        ++requested_path_cursor;
        ++archive_path_cursor;
      }
      while ( archive_path_char );
      archive_entry_count = g_archive_index_records->count;
    }
    if ( !*archive_path_cursor && !*requested_path_cursor )
      break;
    if ( ++archive_entry_index >= archive_entry_count )
      return nullptr;
  }
  return &g_archive_index_records->entries[archive_entry_index];
}
