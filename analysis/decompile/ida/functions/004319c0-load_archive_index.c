/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_archive_index @ 0x4319c0 */
/* selector: load_archive_index */

// Windows RShellDatInit(char*): decodes and parses the SnailMail.dat archive index, rebases the 12-byte entry paths against the installed ArchiveIndex owner, and opens the backing DAT stream.
unsigned __int8 __cdecl load_archive_index(char *path)
{
  FrontendWidget *title_widget; // edi
  ArchiveIndex *tracked_memory; // esi
  ArchiveIndex *v4; // eax
  int32_t v5; // edx
  int v6; // ecx
  char *v7; // esi
  _BYTE Buffer[8]; // [esp+4h] [ebp-7Ch] BYREF
  CompletionResultScreen ElementCount; // [esp+Ch] [ebp-74h]

  g_archive_index_records = nullptr;
  if ( archive_or_file_exists(path, 0) )
  {
    load_file_bytes_fixed_size_from_archive_or_fs(path, Buffer, 124);
    xor_archive_bytes_in_place(0, (int)Buffer, 124);
    title_widget = ElementCount.title_widget;
    tracked_memory = (ArchiveIndex *)allocate_tracked_memory((int)ElementCount.title_widget, aDatFileHeader);
    load_file_bytes_fixed_size_from_archive_or_fs(path, tracked_memory, (int)title_widget);
    xor_archive_bytes_in_place(0, (int)tracked_memory, (int)title_widget);
    v4 = tracked_memory;
    g_archive_index_records = tracked_memory;
    v5 = 0;
    if ( tracked_memory->count > 0 )
    {
      v6 = 0;
      do
      {
        v7 = v4->entries[v6++].path;
        ++v5;
        *(_DWORD *)((char *)v4 + v6 * 12 - 8) = &v7[(_DWORD)v4];
        v4 = g_archive_index_records;
      }
      while ( v5 < g_archive_index_records->count );
    }
    g_archive_file = fopen(path, Mode);
    return 1;
  }
  else
  {
    g_archive_index_records = nullptr;
    return 1;
  }
}
