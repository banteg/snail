/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: set_audio_normalization_scales @ 0x449be0 */
/* selector: set_audio_normalization_scales */

// Stores the normalized music, SFX, and voice gain scales parsed from `VOICE/_VOICE.TXT` into the shared backend lanes that the music, sound, and voice wrappers multiply into live playback volume.
int __thiscall sub_449BE0(_DWORD *this, int a2, int a3, int a4)
{
  *(this + 3) = a2;
  *(this + 4) = a3;
  *(this + 5) = a4;
  return a4;
}

