/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 */
/* selector: load_file_bytes_fixed_size_from_archive_or_fs */

// Windows RShellLoadFileHeader(char*, void*, int): loads exactly the caller-supplied byte count from a named archive entry or filesystem path, using ArchiveEntry data_offset for the sentinel, seek target, and XOR seed while reusing a caller buffer or allocating tracked storage.
void *__cdecl load_file_bytes_fixed_size_from_archive_or_fs(char *path, void *buffer, int byte_count)
{
  int32_t v3; // ebp
  ArchiveEntry *entries; // edi
  char *v5; // edx
  char *v6; // ebx
  char *v7; // esi
  char i; // cl
  char v9; // al
  void *tracked_memory; // edi
  int v12; // eax
  int v13; // eax
  File *v14; // eax
  FILE *v15; // esi
  void *v16; // edi
  char DstBuf[512]; // [esp+14h] [ebp-200h] BYREF

  update_loading_screen(&g_loading_bar);
  if ( g_archive_index_records && (v3 = 0, g_archive_index_records->count > 0) )
  {
    entries = g_archive_index_records->entries;
    while ( 1 )
    {
      v5 = entries->path;
      v6 = path;
      v7 = path;
      for ( i = *entries->path; i; ++v5 )
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
      ++entries;
      if ( v3 >= g_archive_index_records->count )
        goto LABEL_22;
    }
    tracked_memory = buffer;
    if ( buffer == (void *)-1 )
    {
      return (void *)g_archive_index_records->entries[v3].data_offset;
    }
    else
    {
      if ( buffer )
      {
        v13 = ftell(g_archive_file);
        fseek(g_archive_file, g_archive_index_records->entries[v3].data_offset - v13, 1);
        fread(buffer, 1, byte_count, g_archive_file);
        xor_archive_bytes_in_place(g_archive_index_records->entries[v3].data_offset, (int)buffer, byte_count);
      }
      else
      {
        tracked_memory = allocate_tracked_memory(byte_count, path);
        v12 = ftell(g_archive_file);
        fseek(g_archive_file, g_archive_index_records->entries[v3].data_offset - v12, 1);
        fread(tracked_memory, 1, byte_count, g_archive_file);
        xor_archive_bytes_in_place(g_archive_index_records->entries[v3].data_offset, (int)tracked_memory, byte_count);
      }
      return tracked_memory;
    }
  }
  else
  {
    v6 = path;
LABEL_22:
    v14 = fopen(v6, Mode);
    v15 = v14;
    if ( v14 )
    {
      get_stream_length_preserve_position(v14);
      v16 = buffer;
      if ( !buffer || buffer == (void *)-1 )
        v16 = allocate_tracked_memory(byte_count, path);
      fread(v16, 1, byte_count, v15);
      fclose(v15);
      return v16;
    }
    else
    {
      getcwd(DstBuf, 512);
      report_messagef("WARNING:Cannot find file : %s (from %s)\n", v6, DstBuf);
      return nullptr;
    }
  }
}
