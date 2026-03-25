/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: prepare_music_stream_reload_if_path_changed @ 0x4497e0 */
/* selector: prepare_music_stream_reload_if_path_changed */

// Checks whether the requested music path differs from the cached active path and, when it does, stops the current music stream so `cache_music_file` can reload it from archive bytes.
char __thiscall prepare_music_stream_reload_if_path_changed(_BYTE *this, char *a2)
{
  if ( *this )
  {
    if ( sub_44E6C0(a2, byte_7516A0) )
      return 0;
    stop_music_stream(this);
  }
  return 1;
}

