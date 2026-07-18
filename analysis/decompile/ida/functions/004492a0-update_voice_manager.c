/* database: /Users/banteg/dev/banteg/snail-mail/artifacts/ida/SnailMail_unwrapped.exe.i64 */
/* function: update_voice_manager @ 0x4492a0 */
/* selector: update_voice_manager */

// Exact `cRVoiceManager::AI()` member: advances all 16 inline VoiceSets and the manager's global voice-frequency timer.
void __thiscall update_voice_manager(VoiceManager *manager)
{
  VoiceSet *set_cursor; // esi
  int v3; // edi

  set_cursor = (VoiceSet *)manager;
  v3 = 16;
  do
  {
    update_voice_set(set_cursor++);
    --v3;
  }
  while ( v3 );
  manager->global_progress = manager->global_progress + 0.016666668;
}
