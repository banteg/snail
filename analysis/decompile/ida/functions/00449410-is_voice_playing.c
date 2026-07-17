/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: is_voice_playing @ 0x449410 */
/* selector: is_voice_playing */

int32_t __thiscall is_voice_playing(VoiceManager *manager)
{
  int v2; // ebx
  VoiceManager *i; // edi
  int v4; // esi

  v2 = 0;
  for ( i = manager; ; i = (VoiceManager *)((char *)i + 24) )
  {
    v4 = 0;
    if ( (int)i->sets[0].sample_count > 0 )
      break;
LABEL_5:
    if ( ++v2 >= 16 )
      return -1;
  }
  while ( !is_registered_sound_sample_playing(&g_audio_backend, i->sets[0].bites[v4]) )
  {
    if ( ++v4 >= (signed int)i->sets[0].sample_count )
      goto LABEL_5;
  }
  return manager->sets[v2].bites[v4];
}
