/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_archive_index @ 0x4319c0 */
/* selector: load_archive_index */

// Windows RShellDatInit(char*): decodes and parses the SnailMail.dat archive index, rebases the 12-byte entry paths against the installed ArchiveIndex owner, and opens the backing DAT stream.
unsigned __int8 __cdecl load_archive_index(char *path)
{
  int index_byte_count; // edi
  SerializedArchiveIndex *serialized_index; // esi
  ArchiveIndex *archive_index; // eax
  int entry_index; // edx
  int entry_byte_offset; // ecx
  char *rebased_path; // esi
  SerializedArchiveHeader serialized_header; // [esp+4h] [ebp-7Ch] BYREF

  g_archive_index_records = nullptr;
  if ( archive_or_file_exists(path, 0) )
  {
    load_file_bytes_fixed_size_from_archive_or_fs(path, &serialized_header, 124);
    xor_archive_bytes_in_place(0, (int)&serialized_header, 124);
    index_byte_count = serialized_header.entries[0].data_offset;
    serialized_index = (SerializedArchiveIndex *)allocate_tracked_memory(
                                                   serialized_header.entries[0].data_offset,
                                                   aDatFileHeader);
    load_file_bytes_fixed_size_from_archive_or_fs(path, serialized_index, index_byte_count);
    xor_archive_bytes_in_place(0, (int)serialized_index, index_byte_count);
    archive_index = (ArchiveIndex *)serialized_index;
    g_archive_index_records = (ArchiveIndex *)serialized_index;
    entry_index = 0;
    if ( serialized_index->count > 0 )
    {
      entry_byte_offset = 0;
      do
      {
        rebased_path = archive_index->entries[entry_byte_offset++].path;
        ++entry_index;
        *(_DWORD *)((char *)archive_index + entry_byte_offset * 12 - 8) = &rebased_path[(_DWORD)archive_index];
        archive_index = g_archive_index_records;
      }
      while ( entry_index < g_archive_index_records->count );
    }
    g_archive_file = fopen(path, mode);
    return 1;
  }
  else
  {
    g_archive_index_records = nullptr;
    return 1;
  }
}
