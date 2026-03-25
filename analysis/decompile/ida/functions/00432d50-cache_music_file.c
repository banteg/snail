/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: cache_music_file @ 0x432d50 */
/* selector: cache_music_file */

// Ensures one `music/*.ogg` payload is resident in the shared music-file cache, loading it from the archive or filesystem on first use and reusing the cached bytes afterward.
char __cdecl sub_432D50(char *ArgList)
{
  char *v1; // esi
  char result; // al
  _BYTE *v3; // edi

  if ( !MEMORY[0x53C7F8] )
    return ensure_music_stream_from_path(unk_753C58, ArgList, 1);
  v1 = ArgList;
  result = prepare_music_stream_reload_if_path_changed(unk_753C58, ArgList);
  if ( result )
  {
    v3 = load_file_bytes_from_archive_or_fs(v1, MEMORY[0x53C7E8], (#83 *)&ArgList);
    if ( (int)ArgList >= 409600 )
      report_errorf(aMusicBufferOve);
    return play_music_stream_from_bytes(unk_753C58, v1, (int)v3, (int)ArgList, 1);
  }
  return result;
}

