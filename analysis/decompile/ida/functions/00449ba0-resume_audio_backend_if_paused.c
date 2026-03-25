/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: resume_audio_backend_if_paused @ 0x449ba0 */
/* selector: resume_audio_backend_if_paused */

// Restarts the global BASS backend only when the audio state flag at `backend + 0x18` says the backend is currently paused, then clears that paused flag.
int __thiscall sub_449BA0(_BYTE *this)
{
  int result; // eax

  if ( *(this + 24) == 1 )
  {
    result = MEMORY[0x751660]();
    *(this + 24) = 0;
  }
  return result;
}

