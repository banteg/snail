/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_music_stream_from_bytes @ 0x449820 */
/* selector: play_music_stream_from_bytes */

// Stops any previous active music stream, opens a new BASS stream from already-read music bytes, and starts playback while caching the source path.
int __thiscall play_music_stream_from_bytes(_BYTE *this, char *ArgList, int a3, int a4, char a5)
{
  unsigned int v6; // kr04_4
  int file; // eax
  int result; // eax

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
    result = (*(int (__stdcall **)(int, _DWORD, int))&g_cached_music_path[256])(file, 0, 4);
  else
    result = (*(int (__stdcall **)(int, _DWORD, _DWORD))&g_cached_music_path[256])(file, 0, 0);
  *this = 1;
  return result;
}

