/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: play_voice_manager @ 0x4492d0 */
/* selector: play_voice_manager */

// Exact `cRVoiceManager::Play(int, int, int)` member: applies current-voice and frequency gating, optionally stops the active sample, and dispatches through the selected inline VoiceSet.
bool __thiscall play_voice_manager(VoiceManager *manager, int32_t set_id, uint32_t mode, int32_t sample_override)
{
  int32_t v5; // eax
  bool result; // al

  if ( mode < 2 )
  {
    if ( is_voice_playing(manager) != -1 )
      return 0;
    if ( mode == 1 && manager->global_progress < (double)manager->global_frequency_seconds )
      return 0;
  }
  else if ( mode == 2 )
  {
    v5 = is_voice_playing(manager);
    if ( v5 != -1 )
      stop_registered_sound_sample(&g_audio_backend, v5);
  }
  result = play_voice_set(&manager->sets[set_id], sample_override);
  if ( result && (mode == 1 || mode == 2) )
    manager->global_progress = 0.0;
  return result;
}
