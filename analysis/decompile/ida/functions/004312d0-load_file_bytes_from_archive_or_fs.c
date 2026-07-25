/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_from_archive_or_fs @ 0x4312d0 */
/* selector: load_file_bytes_from_archive_or_fs */

// Windows RShellLoadFile(char*, void*, int*): loads variable-size bytes through the shared ArchiveIndex or filesystem fallback, using ArchiveEntry data_offset and byte_count to seek/read/XOR into a caller buffer or tracked allocation and reporting the selected size when requested.
void *__cdecl load_file_bytes_from_archive_or_fs(char *path, void *buffer, int *out_size)
{
  int32_t count; // eax
  int archive_entry_index; // edi
  ArchiveEntry *archive_entry_cursor; // ebx
  char *archive_path_cursor; // edx
  char *requested_path_cursor; // esi
  char archive_path_char; // cl
  char requested_path_char; // al
  File *filesystem_file; // eax
  File *filesystem_stream; // esi
  void *tracked_memory; // ebx
  int allocation_byte_count_offset; // esi
  int allocation_archive_position; // eax
  int allocation_entry_index; // edi
  int caller_archive_position; // eax
  int caller_entry_index; // esi
  int caller_byte_count_offset; // edi
  int stream_length_preserve_position; // eax
  void *filesystem_output_buffer; // ebx
  int filesystem_byte_count; // edi
  char cwd_buffer[512]; // [esp+14h] [ebp-200h] BYREF

  update_loading_screen(&g_loading_bar);
  if ( g_archive_index_records
    && (count = g_archive_index_records->count, archive_entry_index = 0, g_archive_index_records->count > 0) )
  {
    archive_entry_cursor = g_archive_index_records->entries;
    while ( 1 )
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
        count = g_archive_index_records->count;
      }
      if ( !*archive_path_cursor && !*requested_path_cursor )
        break;
      ++archive_entry_index;
      ++archive_entry_cursor;
      if ( archive_entry_index >= count )
        goto LABEL_15;
    }
    if ( out_size )
      *out_size = g_archive_index_records->entries[archive_entry_index].byte_count;
    tracked_memory = buffer;
    if ( buffer == (void *)-1 )
    {
      return (void *)g_archive_index_records->entries[archive_entry_index].data_offset;
    }
    else
    {
      if ( buffer )
      {
        caller_archive_position = ftell(g_archive_file);
        caller_entry_index = archive_entry_index;
        fseek(
          g_archive_file,
          g_archive_index_records->entries[archive_entry_index].data_offset - caller_archive_position,
          1);
        caller_byte_count_offset = 4 * (3 * archive_entry_index + 3);
        fread(
          buffer,
          1u,
          *(int32_t *)((char *)&g_archive_index_records->count + caller_byte_count_offset),
          g_archive_file);
        xor_archive_bytes_in_place(
          g_archive_index_records->entries[caller_entry_index].data_offset,
          (int)buffer,
          *(int32_t *)((char *)&g_archive_index_records->count + caller_byte_count_offset));
      }
      else
      {
        allocation_byte_count_offset = 4 * (3 * archive_entry_index + 3);
        tracked_memory = allocate_tracked_memory(
                           *(int32_t *)((char *)&g_archive_index_records->count + allocation_byte_count_offset),
                           path);
        allocation_archive_position = ftell(g_archive_file);
        allocation_entry_index = archive_entry_index;
        fseek(
          g_archive_file,
          g_archive_index_records->entries[allocation_entry_index].data_offset - allocation_archive_position,
          1);
        fread(
          tracked_memory,
          1u,
          *(int32_t *)((char *)&g_archive_index_records->count + allocation_byte_count_offset),
          g_archive_file);
        xor_archive_bytes_in_place(
          g_archive_index_records->entries[allocation_entry_index].data_offset,
          (int)tracked_memory,
          *(int32_t *)((char *)&g_archive_index_records->count + allocation_byte_count_offset));
      }
      return tracked_memory;
    }
  }
  else
  {
LABEL_15:
    filesystem_file = fopen(path, mode);
    filesystem_stream = filesystem_file;
    if ( filesystem_file )
    {
      stream_length_preserve_position = get_stream_length_preserve_position(filesystem_file);
      filesystem_output_buffer = buffer;
      filesystem_byte_count = stream_length_preserve_position;
      if ( !buffer || buffer == (void *)-1 )
        filesystem_output_buffer = allocate_tracked_memory(stream_length_preserve_position, path);
      fread(filesystem_output_buffer, 1u, filesystem_byte_count, filesystem_stream);
      fclose(filesystem_stream);
      if ( out_size )
        *out_size = filesystem_byte_count;
      return filesystem_output_buffer;
    }
    else
    {
      getcwd(cwd_buffer, 512);
      report_messagef("WARNING:Cannot find file : %s (from %s)\n", path, cwd_buffer);
      return nullptr;
    }
  }
}
