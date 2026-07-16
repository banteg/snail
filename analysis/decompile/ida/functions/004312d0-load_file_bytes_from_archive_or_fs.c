/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_from_archive_or_fs @ 0x4312d0 */
/* selector: load_file_bytes_from_archive_or_fs */

// Windows RShellLoadFile(char*, void*, int*): loads variable-size bytes through the shared ArchiveIndex or filesystem fallback, using ArchiveEntry data_offset and byte_count to seek/read/XOR into a caller buffer or tracked allocation and reporting the selected size when requested.
void *__cdecl load_file_bytes_from_archive_or_fs(char *path, void *buffer, int *out_size)
{
  int32_t count; // eax
  int32_t v4; // edi
  ArchiveEntry *entries; // ebx
  char *v6; // edx
  char *v7; // esi
  char v8; // cl
  char v9; // al
  File *v10; // eax
  FILE *v11; // esi
  void *tracked_memory; // ebx
  int v14; // esi
  int v15; // eax
  int32_t v16; // edi
  int v17; // eax
  int32_t v18; // esi
  int v19; // edi
  int stream_length_preserve_position; // eax
  void *v21; // ebx
  int v22; // edi
  char DstBuf[512]; // [esp+14h] [ebp-200h] BYREF

  update_loading_screen(&g_loading_bar);
  if ( g_archive_index_records && (count = g_archive_index_records->count, v4 = 0, g_archive_index_records->count > 0) )
  {
    entries = g_archive_index_records->entries;
    while ( 1 )
    {
      v6 = entries->path;
      v7 = path;
      v8 = *entries->path;
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
        count = g_archive_index_records->count;
      }
      if ( !*v6 && !*v7 )
        break;
      ++v4;
      ++entries;
      if ( v4 >= count )
        goto LABEL_15;
    }
    if ( out_size )
      *out_size = g_archive_index_records->entries[v4].byte_count;
    tracked_memory = buffer;
    if ( buffer == (void *)-1 )
    {
      return (void *)g_archive_index_records->entries[v4].data_offset;
    }
    else
    {
      if ( buffer )
      {
        v17 = ftell(g_archive_file);
        v18 = v4;
        fseek(g_archive_file, g_archive_index_records->entries[v4].data_offset - v17, 1);
        v19 = 4 * (3 * v4 + 3);
        fread(buffer, 1, *(int32_t *)((char *)&g_archive_index_records->count + v19), g_archive_file);
        xor_archive_bytes_in_place(
          g_archive_index_records->entries[v18].data_offset,
          (int)buffer,
          *(int32_t *)((char *)&g_archive_index_records->count + v19));
      }
      else
      {
        v14 = 4 * (3 * v4 + 3);
        tracked_memory = allocate_tracked_memory(*(int32_t *)((char *)&g_archive_index_records->count + v14), path);
        v15 = ftell(g_archive_file);
        v16 = v4;
        fseek(g_archive_file, g_archive_index_records->entries[v16].data_offset - v15, 1);
        fread(tracked_memory, 1, *(int32_t *)((char *)&g_archive_index_records->count + v14), g_archive_file);
        xor_archive_bytes_in_place(
          g_archive_index_records->entries[v16].data_offset,
          (int)tracked_memory,
          *(int32_t *)((char *)&g_archive_index_records->count + v14));
      }
      return tracked_memory;
    }
  }
  else
  {
LABEL_15:
    v10 = fopen(path, Mode);
    v11 = v10;
    if ( v10 )
    {
      stream_length_preserve_position = get_stream_length_preserve_position(v10);
      v21 = buffer;
      v22 = stream_length_preserve_position;
      if ( !buffer || buffer == (void *)-1 )
        v21 = allocate_tracked_memory(stream_length_preserve_position, path);
      fread(v21, 1, v22, v11);
      fclose(v11);
      if ( out_size )
        *out_size = v22;
      return v21;
    }
    else
    {
      getcwd(DstBuf, 512);
      report_messagef("WARNING:Cannot find file : %s (from %s)\n", path, DstBuf);
      return nullptr;
    }
  }
}
