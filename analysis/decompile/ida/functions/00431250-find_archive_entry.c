/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: find_archive_entry @ 0x431250 */
/* selector: find_archive_entry */

ArchiveEntry *__cdecl find_archive_entry(char *path)
{
  int32_t count; // eax
  int v2; // ebx
  ArchiveEntry *i; // edi
  char *v4; // edx
  char *v5; // esi
  char v6; // cl
  char v7; // al

  if ( !g_archive_index_records )
    return nullptr;
  count = g_archive_index_records->count;
  v2 = 0;
  if ( g_archive_index_records->count <= 0 )
    return nullptr;
  for ( i = g_archive_index_records->entries; ; ++i )
  {
    v4 = i->path;
    v5 = path;
    v6 = *i->path;
    if ( v6 )
    {
      do
      {
        v7 = *v5;
        if ( !*v5 )
          break;
        if ( v7 >= 97 && v7 <= 122 )
          v7 -= 32;
        if ( v6 != v7 )
          break;
        v6 = v4[1];
        ++v5;
        ++v4;
      }
      while ( v6 );
      count = g_archive_index_records->count;
    }
    if ( !*v4 && !*v5 )
      break;
    if ( ++v2 >= count )
      return nullptr;
  }
  return &g_archive_index_records->entries[v2];
}
