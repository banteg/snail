/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_music_stream_from_bytes @ 0x449820 */
/* selector: play_music_stream_from_bytes */

// Stops any previous active music stream, opens a new BASS stream from already-read music bytes, and starts playback while caching the source path.
int __thiscall sub_449820(_BYTE *this, char *ArgList, int a3, int a4, char a5)
{
  unsigned int v6; // kr04_4
  int File; // eax
  int result; // eax

  v6 = strlen(ArgList) + 1;
  sub_44E5B0(&byte_7516A0, ArgList);
  if ( unk_753C20 )
    stop_music_stream(this);
  unk_753C20 = 0;
  if ( (int)(v6 - 1) <= 4 )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  File = MEMORY[0x753BF8](1, a3, 0, a4, 0);
  unk_753C20 = File;
  if ( !File )
    return report_errorf("Music Play Memory Failed %s", ArgList);
  if ( a5 )
    result = MEMORY[0x7517A0](File, 0, 4);
  else
    result = MEMORY[0x7517A0](File, 0, 0);
  *this = 1;
  return result;
}

