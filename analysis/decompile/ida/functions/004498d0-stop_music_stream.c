/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: stop_music_stream @ 0x4498d0 */
/* selector: stop_music_stream */

// Stops the active BASS music stream, removes any registered sync callback, frees the stream handle, and clears the active-stream flag.
int __thiscall sub_4498D0(_BYTE *this)
{
  int result; // eax

  if ( *this )
  {
    if ( unk_751680 )
    {
      MEMORY[0x75165C](unk_753C20, unk_751680);
      unk_751680 = 0;
    }
    MEMORY[0x753BE4](unk_753C20);
    result = MEMORY[0x753CB0](unk_753C20);
    *this = 0;
  }
  return result;
}

