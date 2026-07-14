/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: cache_music_file @ 0x432d50 */
/* selector: cache_music_file */

// Ensures one `music/*.ogg` payload is resident in the shared music-file cache, loading it from the archive or filesystem on first use and reusing the cached bytes afterward.
char __cdecl cache_music_file(char *path, int32_t unused, char *unused_default_path)
{
  char *v3; // esi
  char result; // al
  _BYTE *file_bytes_from_archive_or_fs; // edi

  if ( !g_archive_index_records )
    return ensure_music_stream_from_path(g_audio_backend, path, 1);
  v3 = path;
  result = prepare_music_stream_reload_if_path_changed(g_audio_backend, path);
  if ( result )
  {
    file_bytes_from_archive_or_fs = load_file_bytes_from_archive_or_fs(
                                      v3,
                                      g_music_memory_buffer,
                                      (CompletionResultScreen *)&path);
    if ( (int)path >= 409600 )
      report_errorf(aMusicBufferOve);
    return play_music_stream_from_bytes(g_audio_backend, v3, (int)file_bytes_from_archive_or_fs, (int)path, 1);
  }
  return result;
}

