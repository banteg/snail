/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_voice_playing @ 0x449410 */
/* selector: is_voice_playing */

int __thiscall is_voice_playing(int *this)
{
  int v2; // ebx
  int *i; // edi
  int v4; // esi

  v2 = 0;
  for ( i = this; ; i += 6 )
  {
    v4 = 0;
    if ( *i > 0 )
      break;
LABEL_5:
    if ( ++v2 >= 16 )
      return -1;
  }
  while ( !is_registered_sound_sample_playing((AudioBackend *)g_audio_backend, *(_DWORD *)(i[3] + 4 * v4)) )
  {
    if ( ++v4 >= *i )
      goto LABEL_5;
  }
  return *(_DWORD *)(*(this + 6 * v2 + 3) + 4 * v4);
}
