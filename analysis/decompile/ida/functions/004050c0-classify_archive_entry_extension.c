/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: classify_archive_entry_extension @ 0x4050c0 */
/* selector: classify_archive_entry_extension */

// Copies one archive entry's filename stem before the first dot into the caller buffer and returns the shared ArchiveEntryExtensionClass: TGA, WAV, MP3, or UNKNOWN.
ArchiveEntryExtensionClass __cdecl classify_archive_entry_extension(unsigned __int8 *path, unsigned __int8 *stem_out)
{
  unsigned __int8 *path_cursor; // eax
  unsigned __int8 current_char; // cl
  unsigned __int8 extension_first_char; // cl
  unsigned __int8 *extension_cursor; // eax

  path_cursor = path;
  for ( current_char = *path; *path_cursor; current_char = *path_cursor )
  {
    if ( current_char == 46 )
      break;
    ++path_cursor;
    *stem_out++ = current_char;
  }
  *stem_out = 0;
  if ( !*path_cursor )
    return ARCHIVE_ENTRY_EXTENSION_UNKNOWN;
  extension_first_char = path_cursor[1];
  extension_cursor = path_cursor + 1;
  if ( extension_first_char == 84 && extension_cursor[1] == 71 && extension_cursor[2] == 65 )
    return ARCHIVE_ENTRY_EXTENSION_TGA;
  if ( extension_first_char == 87 && extension_cursor[1] == 65 && extension_cursor[2] == 86 )
    return ARCHIVE_ENTRY_EXTENSION_WAV;
  if ( extension_first_char == 77 && extension_cursor[1] == 80 && extension_cursor[2] == 51 )
    return ARCHIVE_ENTRY_EXTENSION_MP3;
  else
    return ARCHIVE_ENTRY_EXTENSION_UNKNOWN;
}
