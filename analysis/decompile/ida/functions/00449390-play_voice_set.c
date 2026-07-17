/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_voice_set @ 0x449390 */
/* selector: play_voice_set */

bool __thiscall play_voice_set(VoiceSet *set, int32_t sample_override)
{
  uint32_t sample_count; // ecx
  uint32_t v4; // eax

  if ( set->cooldown != 0.0 )
    return 0;
  set->cooldown = set->cooldown_step;
  if ( sample_override == -1 )
  {
    play_voice_backend(set->bites[set->playlist[set->next_index]], 1.0, -1.0, 0.0);
    sample_count = set->sample_count;
    v4 = set->next_index + 1;
    set->next_index = v4;
    if ( v4 == sample_count )
    {
      set->next_index = 0;
      return 1;
    }
  }
  else
  {
    play_voice_backend(sample_override, 1.0, -1.0, 0.0);
  }
  return 1;
}
