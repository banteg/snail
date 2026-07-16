/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: ensure_music_stream_from_path @ 0x449720 */
/* selector: ensure_music_stream_from_path */

// Ensures the requested music path is the active BASS stream, skipping a restart when the cached path already matches and otherwise stopping any previous stream before opening and playing the new path.
int __thiscall ensure_music_stream_from_path(_BYTE *this, char *ArgList, char a3)
{
  int result; // eax
  unsigned int v5; // kr04_4
  int32_t file; // eax

  if ( *this )
  {
    result = strings_equal_case_insensitive_path(ArgList, g_cached_music_path);
    if ( result )
      return result;
    stop_music_stream(this);
  }
  v5 = strlen(ArgList) + 1;
  rstrcpy_checked_ascii(g_cached_music_path, ArgList);
  if ( g_active_music_stream )
    stop_music_stream(this);
  g_active_music_stream = 0;
  if ( (int)(v5 - 1) <= 4 )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  file = g_bass_stream_create_file(0, ArgList, 0, 0, 0);
  g_active_music_stream = file;
  if ( !file )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  if ( a3 )
    result = g_bass_channel_play(file, 0, 4);
  else
    result = g_bass_channel_play(file, 0, 0);
  *this = 1;
  return result;
}
