/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: ensure_music_stream_from_path @ 0x449720 */
/* selector: ensure_music_stream_from_path */

// Ensures the requested music path is the active BASS stream, skipping a restart when the cached path already matches and otherwise stopping any previous stream before opening and playing the new path.
int __thiscall ensure_music_stream_from_path(_BYTE *this, char *ArgList, char a3)
{
  int result; // eax
  unsigned int v5; // kr04_4
  int v6; // eax

  if ( *this )
  {
    result = sub_44E6C0(ArgList, byte_7516A0);
    if ( result )
      return result;
    stop_music_stream(this);
  }
  v5 = strlen(ArgList) + 1;
  sub_44E5B0(byte_7516A0, ArgList);
  if ( unk_753C20 )
    stop_music_stream(this);
  unk_753C20 = 0;
  if ( (int)(v5 - 1) <= 4 )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  v6 = MEMORY[0x753BF8](0, ArgList, 0, 0, 0);
  unk_753C20 = v6;
  if ( !v6 )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  if ( a3 )
    result = (*(int (__stdcall **)(int, _DWORD, int))&byte_7516A0[256])(v6, 0, 4);
  else
    result = (*(int (__stdcall **)(int, _DWORD, _DWORD))&byte_7516A0[256])(v6, 0, 0);
  *this = 1;
  return result;
}

