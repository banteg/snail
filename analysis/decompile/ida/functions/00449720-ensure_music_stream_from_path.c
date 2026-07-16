/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: ensure_music_stream_from_path @ 0x449720 */
/* selector: ensure_music_stream_from_path */

// Ensures the requested music path is the active BASS stream, skipping a restart when the cached path already matches and otherwise stopping any previous stream before opening and playing the new path.
int32_t __thiscall ensure_music_stream_from_path(AudioBackend *backend, char *path, char play_mode)
{
  int32_t result; // eax
  unsigned int v5; // kr04_4
  BassHandle file; // eax

  if ( backend->music_stream_active )
  {
    result = strings_equal_case_insensitive_path(path, g_cached_music_path);
    if ( result )
      return result;
    stop_music_stream(backend);
  }
  v5 = strlen(path) + 1;
  rstrcpy_checked_ascii(g_cached_music_path, path);
  if ( g_active_music_stream )
    stop_music_stream(backend);
  g_active_music_stream = 0;
  if ( (int)(v5 - 1) <= 4 )
    return report_errorf("Music Play Memory Failed %s", path);
  file = g_bass_stream_create_file(0, path, 0, 0, 0);
  g_active_music_stream = file;
  if ( !file )
    return report_errorf("Music Play Memory Failed %s", path);
  if ( play_mode )
    result = g_bass_stream_play(file, 0, 4u);
  else
    result = g_bass_stream_play(file, 0, 0);
  backend->music_stream_active = 1;
  return result;
}
