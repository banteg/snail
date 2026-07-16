/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_music_stream_from_bytes @ 0x449820 */
/* selector: play_music_stream_from_bytes */

// Stops any previous active music stream, opens a new BASS stream from already-read music bytes, and starts playback while caching the source path.
int32_t __thiscall play_music_stream_from_bytes(
        AudioBackend *backend,
        char *path,
        char *bytes,
        int32_t byte_count,
        char play_mode)
{
  unsigned int v6; // kr04_4
  BassHandle file; // eax
  int32_t result; // eax

  v6 = strlen(path) + 1;
  rstrcpy_checked_ascii(g_cached_music_path, path);
  if ( g_active_music_stream )
    stop_music_stream(backend);
  g_active_music_stream = 0;
  if ( (int)(v6 - 1) <= 4 )
    return report_errorf("Music Play Memory Failed %s", path);
  file = g_bass_stream_create_file(1, bytes, 0, byte_count, 0);
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
