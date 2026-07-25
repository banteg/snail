/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: load_file_bytes_fixed_size_from_archive_or_fs @ 0x431030 */
/* selector: load_file_bytes_fixed_size_from_archive_or_fs */

// Windows RShellLoadFileHeader(char*, void*, int): loads exactly the caller-supplied byte count from a named archive entry or filesystem path, using ArchiveEntry data_offset for the sentinel, seek target, and XOR seed while reusing a caller buffer or allocating tracked storage.
void *__cdecl load_file_bytes_fixed_size_from_archive_or_fs(char *path, void *buffer, int byte_count)
{
  int archive_entry_index; // ebp
  ArchiveEntry *archive_entry_cursor; // edi
  char *archive_path_cursor; // edx
  char *requested_path; // ebx
  char *requested_path_cursor; // esi
  char archive_path_char; // cl
  char requested_path_char; // al
  void *archive_output_buffer; // edi
  int allocation_archive_position; // eax
  int caller_archive_position; // eax
  File *filesystem_file; // eax
  File *filesystem_stream; // esi
  void *filesystem_output_buffer; // edi
  char cwd_buffer[512]; // [esp+14h] [ebp-200h] BYREF

  update_loading_screen(&g_loading_bar);
  if ( g_archive_index_records && (archive_entry_index = 0, g_archive_index_records->count > 0) )
  {
    archive_entry_cursor = g_archive_index_records->entries;
    while ( 1 )
    {
      archive_path_cursor = archive_entry_cursor->path;
      requested_path = path;
      requested_path_cursor = path;
      for ( archive_path_char = *archive_entry_cursor->path; archive_path_char; ++archive_path_cursor )
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
      }
      if ( !*archive_path_cursor && !*requested_path_cursor )
        break;
      ++archive_entry_index;
      ++archive_entry_cursor;
      if ( archive_entry_index >= g_archive_index_records->count )
        goto LABEL_22;
    }
    archive_output_buffer = buffer;
    if ( buffer == (void *)-1 )
    {
      return (void *)g_archive_index_records->entries[archive_entry_index].data_offset;
    }
    else
    {
      if ( buffer )
      {
        caller_archive_position = ftell(g_archive_file);
        fseek(
          g_archive_file,
          g_archive_index_records->entries[archive_entry_index].data_offset - caller_archive_position,
          1);
        fread(buffer, 1u, byte_count, g_archive_file);
        xor_archive_bytes_in_place(
          g_archive_index_records->entries[archive_entry_index].data_offset,
          (int)buffer,
          byte_count);
      }
      else
      {
        archive_output_buffer = allocate_tracked_memory(byte_count, path);
        allocation_archive_position = ftell(g_archive_file);
        fseek(
          g_archive_file,
          g_archive_index_records->entries[archive_entry_index].data_offset - allocation_archive_position,
          1);
        fread(archive_output_buffer, 1u, byte_count, g_archive_file);
        xor_archive_bytes_in_place(
          g_archive_index_records->entries[archive_entry_index].data_offset,
          (int)archive_output_buffer,
          byte_count);
      }
      return archive_output_buffer;
    }
  }
  else
  {
    requested_path = path;
LABEL_22:
    filesystem_file = fopen(requested_path, mode);
    filesystem_stream = filesystem_file;
    if ( filesystem_file )
    {
      get_stream_length_preserve_position(filesystem_file);
      filesystem_output_buffer = buffer;
      if ( !buffer || buffer == (void *)-1 )
        filesystem_output_buffer = allocate_tracked_memory(byte_count, path);
      fread(filesystem_output_buffer, 1u, byte_count, filesystem_stream);
      fclose(filesystem_stream);
      return filesystem_output_buffer;
    }
    else
    {
      getcwd(cwd_buffer, 512);
      report_messagef("WARNING:Cannot find file : %s (from %s)\n", requested_path, cwd_buffer);
      return nullptr;
    }
  }
}
