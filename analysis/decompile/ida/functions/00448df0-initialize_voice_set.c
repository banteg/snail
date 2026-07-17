/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: initialize_voice_set @ 0x448df0 */
/* selector: initialize_voice_set */

void __thiscall initialize_voice_set(VoiceSet *set, int32_t count)
{
  int32_t *tracked_memory; // eax
  int32_t *v4; // eax
  signed int sample_count; // ecx
  signed int v6; // eax
  int v7; // [esp-10h] [ebp-14h]

  set->sample_count = count;
  set->next_index = 0;
  tracked_memory = (int32_t *)allocate_tracked_memory(4 * count, aPlaylist);
  v7 = 4 * set->sample_count;
  set->playlist = tracked_memory;
  v4 = (int32_t *)allocate_tracked_memory(v7, aVoicebite);
  sample_count = set->sample_count;
  set->bites = v4;
  v6 = 0;
  set->cooldown = 0.0;
  set->cooldown_step = 0.0041666669;
  if ( sample_count > 0 )
  {
    do
    {
      set->playlist[v6] = v6;
      ++v6;
    }
    while ( v6 < (signed int)set->sample_count );
  }
  shuffle_voice_set(set);
}
