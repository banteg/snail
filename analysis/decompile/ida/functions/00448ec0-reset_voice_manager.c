/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: reset_voice_manager @ 0x448ec0 */
/* selector: reset_voice_manager */

// Exact `cRVoiceManager::ReSet()` member: clears global voice progress and all 16 inline VoiceSet cooldowns.
void __thiscall reset_voice_manager(VoiceManager *manager)
{
  float *cooldown_cursor; // eax
  int v2; // ecx

  manager->global_progress = 0.0;
  cooldown_cursor = &manager->sets[0].cooldown;
  v2 = 16;
  do
  {
    *cooldown_cursor = 0.0;
    cooldown_cursor += 6;
    --v2;
  }
  while ( v2 );
}
