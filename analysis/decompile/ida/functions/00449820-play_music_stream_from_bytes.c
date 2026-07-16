/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_music_stream_from_bytes @ 0x449820 */
/* selector: play_music_stream_from_bytes */

// Stops any previous active music stream, opens a new BASS stream from already-read music bytes, and starts playback while caching the source path.
int32_t __thiscall play_music_stream_from_bytes(_BYTE *this, char *ArgList, int a3, int a4, char a5)
{
  unsigned int v6; // kr04_4
  int32_t file; // eax
  int32_t result; // eax

  v6 = strlen(ArgList) + 1;
  rstrcpy_checked_ascii(g_cached_music_path, ArgList);
  if ( g_active_music_stream )
    stop_music_stream(this);
  g_active_music_stream = 0;
  if ( (int)(v6 - 1) <= 4 )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  file = g_bass_stream_create_file(1, a3, 0, a4, 0);
  g_active_music_stream = file;
  if ( !file )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  if ( a5 )
    result = g_bass_channel_play(file, 0, 4);
  else
    result = g_bass_channel_play(file, 0, 0);
  *this = 1;
  return result;
}
